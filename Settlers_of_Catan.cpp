//main
#include "Board.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT WINDOW_WIDTH

Board game;

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1);

	glLoadIdentity();
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -10.0f, 10.0f);

	game.DrawBoard();
	game.DrawPieces();

	glutSwapBuffers();

	glutPostRedisplay();
}

void initializePieces(Board *b)
{
	Settlement s;
	s = Settlement(1, { -20, -30 });
	b->AddPiece(&s);
	s = Settlement(2, { -20, -10 });
	b->AddPiece(&s);
	s = Settlement(3, { -20,  10 });
	b->AddPiece(&s);
	s = Settlement(4, { -20,  30 });
	b->AddPiece(&s);

	City c;
	c = City(1, { 0, -30 });
	b->AddPiece(&c);
	c = City(2, { 0, -10 });
	b->AddPiece(&c);
	c = City(3, { 0,  10 });
	b->AddPiece(&c);
	c = City(4, { 0,  30 });
	b->AddPiece(&c);

	Road r;
	r = Road(1, { 20, -30 }, { 30, -20 });
	b->AddPiece(&r);
	r = Road(2, { 20, -10 }, { 30,   0 });
	b->AddPiece(&r);
	r = Road(3, { 20,  10 }, { 30,  20 });
	b->AddPiece(&r);
	r = Road(4, { 20,  30 }, { 30,  40 });
	b->AddPiece(&r);
}

int main(int argc, char * argv[])
{
	game = Board();
	game.SetTiles();

	initializePieces(&game);

	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
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

