#pragma once
#include<GL/glut.h>

#define TILE_SIZE 40.0
#define PIECE_SIZE (TILE_SIZE / 8.0)

struct Point2D
{
	double x;
	double y;
};

Point2D convertNodeToPoint(int nodeIndex);

typedef enum Terrain
{
	Fields,
	Forest,
	Pasture,
	Mountains,
	Hills,
	Desert,
	Sea,
	Harbour,
	None = -1
};

typedef enum PieceType
{
	SETTLEMENT,
	CITY,
	ROAD,
	NA = -1
};

class TerrainTile
{
public:
	Point2D location;
	int number;
	Terrain type;

	TerrainTile();
	TerrainTile(Point2D location, int number, Terrain type);
	void Draw();
};

class Piece
{
public:
	PieceType pieceType;

	Piece();
	virtual void Draw() = 0;
};

class Settlement : public Piece
{
public:
	Point2D location;
	int team;

	Settlement();
	Settlement(int team, Point2D location);
	virtual void Draw();
};

class City : public Piece
{
public:
	Point2D location;
	int team;

	City();
	City(int team, Point2D location);
	virtual void Draw();
};

class Road : public Piece
{
public:
	Point2D start;
	Point2D end;
	int team;

	Road();
	Road(int team, Point2D start, Point2D end);
	virtual void Draw();
};
