#include <math.h>
#include <GL/freeglut.h>
#include <string>
#include "GamePieces.h"

using namespace std;

const unsigned char teamColours[4][3] = {
	{255,0,0},
	{255,255,0},
	{0,0,255},
	{255,255,255}
};

TerrainTile::TerrainTile()
{
}

TerrainTile::TerrainTile(Point2D location, int number, Terrain type)
{
	this->location = location;
	this->number = number;
	this->type = type;
}

void TerrainTile::Draw()
{
	double thirdPi = (3.14159 / 3.0);

	switch (type)
	{
	case Fields:
		glColor3ub(180, 200, 0);
		break;

	case Forest:
		glColor3ub(0, 90, 5);
		break;

	case Pasture:
		glColor3ub(80, 200, 20);
		break;

	case Mountains:
		glColor3ub(90, 130, 160);
		break;

	case Hills:
		glColor3ub(100, 70, 10);
		break;

	case Desert:
		glColor3ub(160, 150, 90);
		break;

	case Sea:
		glColor3ub(20, 150, 255);
		break;

	case Harbour:
		glColor3ub(0, 100, 180);
		break;

	default:
		break;

	};

	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(location.x, location.y);

	for (int i = 0; i < 7; i++)
	{
		double angle = thirdPi * i;
		double yOffset = (TILE_SIZE / 2.0) * cos(angle);
		double xOffset = (TILE_SIZE / 2.0) * sin(angle);

		glVertex2f(location.x + xOffset, location.y + yOffset);
	}

	glEnd();

	char num[3];
	itoa(number, num, 10);

	if (number == 7)
		glColor3ub(255, 0, 0);
	else
		glColor3ub(0, 0, 0);

	glLineWidth(3);

	glPushMatrix();
	glTranslatef(location.x - 3, location.y - 2, 1);
	glScalef(0.05, 0.05, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)num);
	glPopMatrix();

	glColor3ub(255, 255, 255);
}

Settlement::Settlement()
{
	this->pieceType = SETTLEMENT;
}

Settlement::Settlement(int team, Point2D location)
{
	this->pieceType = SETTLEMENT;
	this->team = team;
	this->location = location;
}

void Settlement::Draw()
{
	glColor3ub(teamColours[team - 1][0], teamColours[team - 1][1], teamColours[team - 1][2]);

	glBegin(GL_QUADS);

	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y + (PIECE_SIZE / 2.0), 2.0);
	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y + (PIECE_SIZE / 2.0), 2.0);

	glEnd();

	glColor3ub(teamColours[team - 1][0] * 2 / 3, teamColours[team - 1][1] * 2 / 3, teamColours[team - 1][2] * 2 / 3);

	glBegin(GL_QUADS);

	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y - (PIECE_SIZE / 2.0), 2.0);
	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y - (PIECE_SIZE / 2.0), 2.0);

	glEnd();

	glColor3ub(255, 255, 255);
}

City::City()
{
	this->pieceType = CITY;
}

City::City(int team, Point2D location)
{
	this->pieceType = CITY;
	this->team = team;
	this->location = location;
}

void City::Draw()
{
	glColor3ub(teamColours[team - 1][0], teamColours[team - 1][1], teamColours[team - 1][2]);

	glBegin(GL_QUADS);

	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y + (PIECE_SIZE / 2.0), 2.0f);
	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y + (PIECE_SIZE / 2.0), 2.0f);

	glEnd();

	glColor3ub(teamColours[team - 1][0] * 2 / 3, teamColours[team - 1][1] * 2 / 3, teamColours[team - 1][2] * 2 / 3);

	glBegin(GL_QUADS);

	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y - (PIECE_SIZE / 2.0), 2.0);
	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y - (PIECE_SIZE / 2.0), 2.0);

	glEnd();

	glColor3ub(teamColours[team - 1][0] * 3 / 4, teamColours[team - 1][1] * 3 / 4, teamColours[team - 1][2] * 3 / 4);

	glBegin(GL_QUADS);

	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y + (PIECE_SIZE / 2.0), 2.0);
	glVertex3f(location.x + (PIECE_SIZE),		location.y + (PIECE_SIZE / 2.0), 2.0);
	glVertex3f(location.x + (PIECE_SIZE),		location.y - (PIECE_SIZE / 2.0), 2.0);
	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y - (PIECE_SIZE / 2.0), 2.0);

	glEnd();

	glColor3ub(255, 255, 255);
}

Road::Road()
{
	this->pieceType = ROAD;
}

Road::Road(int team, Point2D start, Point2D end)
{
	this->pieceType = ROAD;
	this->team = team;
	this->start = start;
	this->end = end;
}

void Road::Draw()
{
	double angle = atan2((end.y - start.y), (end.x - start.x)) * (180.0 / 3.14159);
	double length = sqrt(pow((end.y - start.y), 2) + pow((end.x - start.x), 2));

	glColor3ub(teamColours[team - 1][0], teamColours[team - 1][1], teamColours[team - 1][2]);

	glPushMatrix();
	glTranslatef(start.x, start.y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(length, (PIECE_SIZE / 2.0), 1);


	glBegin(GL_QUADS);

	glVertex3f(0, 0.5, 2.0);
	glVertex3f(1, 0.5, 2.0);
	glVertex3f(1, -0.5, 2.0);
	glVertex3f(0, -0.5, 2.0);

	glEnd();

	glPopMatrix();

	glColor3ub(255, 255, 255);
}

Piece::Piece()
{
	this->pieceType = NA;
}

Point2D convertNodeToPoint(int nodeIndex)
{
	const int width = (TILE_SIZE * 0.433);
	const int height = (TILE_SIZE * 0.25);

	const int columns[11][6] = {
		{ 21,27,-1,-1,-1,-1 },
		{ 11,16,33,38,-1,-1 },
		{ 3,7,22,28,43,47 },
		{ 0,12,17,34,39,51 },
		{ 4,8,23,29,44,48 },
		{ 1,13,18,35,40,52 },
		{ 5,9,24,30,45,49 },
		{ 2,14,19,36,41,53 },
		{ 6,10,25,31,46,50 },
		{ 15,20,37,42,-1,-1 },
		{ 26,32,-1,-1,-1,-1 }
	};

	Point2D pt;

	if (nodeIndex <= 2)			
		pt.y = height * 8;
	else if (nodeIndex <= 6)	
		pt.y = height * 7;
	else if (nodeIndex <= 10)	
		pt.y = height * 5;
	else if (nodeIndex <= 15)	
		pt.y = height * 4;
	else if (nodeIndex <= 20)	
		pt.y = height * 2;
	else if (nodeIndex <= 26)	
		pt.y = height;
	else if (nodeIndex <= 32)	
		pt.y = -height;
	else if (nodeIndex <= 37)	
		pt.y = -height * 2;
	else if (nodeIndex <= 42)	
		pt.y = -height * 4;
	else if (nodeIndex <= 46)	
		pt.y = -height * 5;
	else if (nodeIndex <= 50)	
		pt.y = -height * 7;
	else						
		pt.y = height * 8;

	for (int i = 0; i < 11; i++)
	{
		if (nodeIndex < columns[i][0])
			continue;

		for (int j = 0; j < 6; j++)
		{
			if (nodeIndex < columns[i][j])
				break;

			else if (nodeIndex == columns[i][j])
			{
				pt.x = (i - 5) * width;
				return pt;
			}
		}
	}

	return {90, 90};
}
