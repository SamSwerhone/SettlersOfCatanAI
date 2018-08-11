//main
#include "GameBoard.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT WINDOW_WIDTH

#define DEBUG 1

Board *boardptr;
GameBoard *gameptr;

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1);

	glLoadIdentity();
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -10.0f, 10.0f);

	gameptr->DrawBoard();
	gameptr->DrawPieces();

	glutSwapBuffers();

	glutPostRedisplay();
}

void NextMove(player p)
{
	int node = boardptr->get_best_open_node();
	boardptr->ownNode(p, node);

	Point2D pt = convertNodeToPoint(node);
	Settlement s = Settlement((int)p, pt);
	gameptr->AddPiece(&s);

#if DEBUG
	std::cout << "Player " << (int)p << ": " << node << ", (" << pt.x << "," << pt.y << ")" << std::endl;
#endif
}

int main(int argc, char * argv[])
{
	Board board = Board();
	GameBoard game = GameBoard();

	boardptr = &board;
	gameptr = &game;

	game.SetBoard(&board);

#if DEBUG
	board.updateFutureValues();
	NextMove(BLUE);
	board.updateFutureValues();
	NextMove(RED);
	board.updateFutureValues();
	NextMove(WHITE);
	board.updateFutureValues();
	NextMove(YELLOW);
#endif

	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("Settlers of Catan");
	glutDisplayFunc(Draw);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);

	glutMainLoop();

	return 0;
}

