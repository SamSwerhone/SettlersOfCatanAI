#include <math.h>
#include "GamePieces.h"

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
	unsigned char colour[3] = {0, 0, 0};

	switch (team)
	{
	case 1:
		colour[1] = 128;
		colour[2] = 255;
		break;

	case 2:
		colour[0] = 255;
		colour[1] = 255;
		colour[2] = 255;
		break;

	case 3:
		colour[0] = 255;
		break;

	case 4:
		colour[0] = 255;
		colour[1] = 128;
		break;

	default:
		break;
	}

	glColor3ub(colour[0], colour[1], colour[2]);

	glBegin(GL_QUADS);

	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y + (PIECE_SIZE / 2.0), 2.0);
	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y + (PIECE_SIZE / 2.0), 2.0);

	glEnd();

	glColor3ub(colour[0] * 2 / 3, colour[1] * 2 / 3, colour[2] * 2 / 3);

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
	unsigned char colour[3] = { 0, 0, 0 };

	switch (team)
	{
	case 1:
		colour[1] = 128;
		colour[2] = 255;
		break;

	case 2:
		colour[0] = 255;
		colour[1] = 255;
		colour[2] = 255;
		break;

	case 3:
		colour[0] = 255;
		break;

	case 4:
		colour[0] = 255;
		colour[1] = 128;
		break;

	default:
		break;
	}

	glColor3ub(colour[0], colour[1], colour[2]);

	glBegin(GL_QUADS);

	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y + (PIECE_SIZE / 2.0), 2.0f);
	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y + (PIECE_SIZE / 2.0), 2.0f);

	glEnd();

	glColor3ub(colour[0] * 2 / 3, colour[1] * 2 / 3, colour[2] * 2 / 3);

	glBegin(GL_QUADS);

	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y, 2.0);
	glVertex3f(location.x - (PIECE_SIZE / 2.0), location.y - (PIECE_SIZE / 2.0), 2.0);
	glVertex3f(location.x + (PIECE_SIZE / 2.0), location.y - (PIECE_SIZE / 2.0), 2.0);

	glEnd();

	glColor3ub(colour[0] * 3 / 4, colour[1] * 3 / 4, colour[2] * 3 / 4);

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
	unsigned char colour[3] = { 0, 0, 0 };

	switch (team)
	{
	case 1:
		colour[1] = 128;
		colour[2] = 255;
		break;

	case 2:
		colour[0] = 255;
		colour[1] = 255;
		colour[2] = 255;
		break;

	case 3:
		colour[0] = 255;
		break;

	case 4:
		colour[0] = 255;
		colour[1] = 128;
		break;

	default:
		break;
	}

	double angle = atan2((end.y - start.y), (end.x - start.x)) * (180.0 / 3.14159);
	double length = sqrt(pow((end.y - start.y), 2) + pow((end.x - start.x), 2));

	glColor3ub(colour[0], colour[1], colour[2]);

	glPushMatrix();
	glTranslatef(start.x, start.y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(length, (PIECE_SIZE / 2.0), 1);


	glBegin(GL_QUADS);

	glVertex3f(0, 0.5, 1.0);
	glVertex3f(1, 0.5, 1.0);
	glVertex3f(1, -0.5, 1.0);
	glVertex3f(0, -0.5, 1.0);

	glEnd();

	glPopMatrix();

	glColor3ub(255, 255, 255);
}

Piece::Piece()
{
	this->pieceType = NONE;
}
