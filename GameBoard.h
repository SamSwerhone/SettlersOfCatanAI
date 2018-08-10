#pragma once
#include <vector>
#include "GamePieces.h"
#include "Settlers_Classes.h"

#define TILE_WIDTH  (TILE_SIZE * 0.866)
#define TILE_HEIGHT (TILE_SIZE * 0.75)

class GameBoard
{
public:
	GameBoard();

	void SetBoard(Board *board);
	void DrawBoard();
	void AddPiece(Piece * p);
	void DrawPieces();

private:
	Board *board;
	const Point2D hexes[19] = {
	{ -TILE_WIDTH, (TILE_HEIGHT * 2.0) },		{ 0, (TILE_HEIGHT * 2.0) },		{ TILE_WIDTH, (TILE_HEIGHT * 2.0) },

	{ -(TILE_WIDTH * 1.5), TILE_HEIGHT },	{ -(TILE_WIDTH * 0.5), TILE_HEIGHT },	{ (TILE_WIDTH * 0.5), TILE_HEIGHT },		{ (TILE_WIDTH * 1.5), TILE_HEIGHT },

	{ -(TILE_WIDTH * 2.0), 0 },		{ -TILE_WIDTH, 0 },		{ 0, 0 },		{ TILE_WIDTH, 0 },		{ (TILE_WIDTH * 2.0), 0 },

	{ -(TILE_WIDTH * 1.5), -TILE_HEIGHT },	{ -(TILE_WIDTH * 0.5), -TILE_HEIGHT },	{ (TILE_WIDTH * 0.5), -TILE_HEIGHT },	{ (TILE_WIDTH * 1.5), -TILE_HEIGHT },

	{ -TILE_WIDTH, -(TILE_HEIGHT * 2.0) },		{ 0, -(TILE_HEIGHT * 2.0) },		{ TILE_WIDTH, -(TILE_HEIGHT * 2.0) }
	};

	TerrainTile tiles[19];

	std::vector<Settlement> settlements;
	std::vector<City> cities;
	std::vector<Road> roads;
};