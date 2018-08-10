#pragma once
#include <vector>
#include "Pieces/GamePieces.h"

class Board
{
public:
	Board();

	void SetTiles();
	void DrawBoard();
	void AddPiece(Piece * p);
	void DrawPieces();

private:
	int numbers[18] = { 2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12 };
	Point2D hexes[19] = {
	{ -TILE_SIZE, (TILE_SIZE * 1.8) },		{ 0, (TILE_SIZE * 1.8) },		{ TILE_SIZE, (TILE_SIZE * 1.8) },

	{ -(TILE_SIZE * 3.0 / 2.0), (TILE_SIZE * 0.9) },	{ -(TILE_SIZE / 2.0), (TILE_SIZE * 0.9) },	{ (TILE_SIZE / 2.0), (TILE_SIZE * 0.9) },		{ (TILE_SIZE * 3.0 / 2.0), (TILE_SIZE * 0.9) },

	{ -(TILE_SIZE * 2.0), 0 },		{ -TILE_SIZE, 0 },		{ 0, 0 },		{ TILE_SIZE, 0 },		{ (TILE_SIZE * 2.0), 0 },

	{ -(TILE_SIZE * 3.0 / 2.0), -(TILE_SIZE * 0.9) },	{ -(TILE_SIZE / 2.0), -(TILE_SIZE * 0.9) },	{ (TILE_SIZE / 2.0), -(TILE_SIZE * 0.9) },	{ (TILE_SIZE * 3.0 / 2.0), -(TILE_SIZE * 0.9) },

	{ -TILE_SIZE, -(TILE_SIZE * 1.8) },		{ 0, -(TILE_SIZE * 1.8) },		{ TILE_SIZE, -(TILE_SIZE * 1.8) }
	};

	TerrainTile tiles[19];

	std::vector<Settlement> settlements;
	std::vector<City> cities;
	std::vector<Road> roads;
};