//main
#include "GameBoard.h"
#include "AntTweakBar.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT WINDOW_WIDTH

Board *boardptr;
GameBoard *gameptr;
int playerIter = 0;
bool negativeIter = false;
player moves[4] = { RED, YELLOW, BLUE, WHITE};
int numplayers = 2;
float player1[3] = {1.0,0.0,0.0};
float player2[3] = {1.0,1.0,0.0};
float player3[3] = {0.0,0.0,1.0};
float player4[3] = {1.0,1.0,1.0};

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1);

	glLoadIdentity();
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -10.0f, 10.0f);

	gameptr->DrawBoard();
	gameptr->DrawPieces();

#ifdef TW_INCLUDED
	// Draw tweak bars
	TwDraw();
#endif

	glutSwapBuffers();
	glutPostRedisplay();
}

void RegenerateBoard()
{
	boardptr = new Board();
	gameptr->SetBoard(boardptr);
	playerIter = 0;
	negativeIter = false;
	glutPostRedisplay();
	//reset the players pieces?
}

void NextMove(player p)
{
	boardptr->updateFutureValues();
	boardptr->rankNodes();
	int node = boardptr->get_best_open_node();
	boardptr->ownNode(p, node);

	Point2D pt = convertNodeToPoint(node);
	Settlement s = Settlement((int)p, pt);
	gameptr->AddPiece(&s);
}

#ifdef TW_INCLUDED
void TW_CALL button_callback1(void * clientData)
{
	RegenerateBoard();
}

void TW_CALL button_callback2(void * clientData)
{
	if (playerIter == numplayers-1 && negativeIter == false)
	{
		NextMove(moves[playerIter]);
		negativeIter = true;
	}
	
	else if (negativeIter == true)
	{
		if (playerIter == -1)
		{
			return;
		}
		
		NextMove(moves[playerIter]);
		playerIter--;
	}
	
	else
	{
		NextMove(moves[playerIter]);
		playerIter++;
	}
}

void initTweak()
{
	TwBar *bar;					// Pointer to a tweak bar		
	TwInit(TW_OPENGL, NULL);	// Initialize AntTweakBar

	// Set GLUT event callbacks
	// - Directly redirect GLUT mouse button events to AntTweakBar
	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	// - Directly redirect GLUT mouse motion events to AntTweakBar
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	// - Directly redirect GLUT mouse "passive" motion events to AntTweakBar (same as MouseMotion)
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	// - Send 'glutGetModifers' function pointer to AntTweakBar;
	glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
	//   required because the GLUT key event functions do not report key modifiers states.
	TwGLUTModifiersFunc(glutGetModifiers);

	bar = TwNewBar("User Interface");
	//TwDefine(" help='Manipulate the robot'"); // Message added to the help bar.
	TwDefine("'User Interface' color='192 192 192' size = '250 150' position = '0 10'"); // size (x,y) colour (r,g,b)
	TwAddVarRW(bar, "Number of Players:", TW_TYPE_INT32, &numplayers, "min=2 max=4 step 1");
	TwAddVarRO(bar, "Player 1:", TW_TYPE_COLOR3F, player1, "");
	TwAddVarRO(bar, "Player 2:", TW_TYPE_COLOR3F, player2, "");
	TwAddVarRO(bar, "Player 3:", TW_TYPE_COLOR3F, player3, "");
	TwAddVarRO(bar, "Player 4:", TW_TYPE_COLOR3F, player4, "");
	TwAddButton(bar, "Regenerate Board:", button_callback1, NULL, "");
	TwAddButton(bar, "Next Move:", button_callback2, NULL, "");

	TwWindowSize(720, 720);
}

#endif

void Terminate()
{
#ifdef TW_INCLUDED
	TwTerminate();
#endif
}

int main(int argc, char * argv[])
{
	Board board = Board();
	GameBoard game = GameBoard();

	boardptr = &board;
	gameptr = &game;

	game.SetBoard(&board);

	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("Settlers of Catan");
	glutDisplayFunc(Draw);

#ifdef TW_INCLUDED
	initTweak();
#endif

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);

	glutMainLoop();

	Terminate();

	return 0;
}

