#pragma once
#include<GL/glut.h>

#define TILE_SIZE 30.0
#define PIECE_SIZE (TILE_SIZE / 4.0)

struct Point2D
{
	double x;
	double y;
};

enum Terrain
{
	Fields,
	Forest,
	Pasture,
	Mountains,
	Hills,
	Desert,
	Sea,
	Harbour
};

enum PieceType
{
	SETTLEMENT,
	CITY,
	ROAD,
	NONE = -1
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
