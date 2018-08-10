#include <algorithm>
#include <time.h>
#include "Board.h"

Board::Board()
{
	srand(time(0));

	// shuffle number tokens
	std::random_shuffle(&numbers[0], &numbers[18]);

	// shuffle tile locations
	std::random_shuffle(&hexes[0], &hexes[19]);
}

void Board::SetTiles()
{
	int i = 0;

	tiles[i++].type = Fields;
	tiles[i++].type = Fields;
	tiles[i++].type = Fields;
	tiles[i++].type = Fields;

	tiles[i++].type = Forest;
	tiles[i++].type = Forest;
	tiles[i++].type = Forest;
	tiles[i++].type = Forest;

	tiles[i++].type = Pasture;
	tiles[i++].type = Pasture;
	tiles[i++].type = Pasture;
	tiles[i++].type = Pasture;

	tiles[i++].type = Mountains;
	tiles[i++].type = Mountains;
	tiles[i++].type = Mountains;

	tiles[i++].type = Hills;
	tiles[i++].type = Hills;
	tiles[i++].type = Hills;

	tiles[i++].type = Desert;

	int index = 0;
	for (int j = 0; j < 19; j++)
	{
		if (tiles[j].type != Desert)
		{
			tiles[j].number = numbers[index++];
		}

		tiles[j].location = hexes[j];
	}
}

void Board::DrawBoard()
{
	for (int i = 0; i < 19; i++)
	{
		tiles[i].Draw();
	}
}

void Board::AddPiece(Piece * p)
{
	switch (p->pieceType)
	{
	case SETTLEMENT:
		settlements.push_back(Settlement(*((Settlement*)p)));
		break;

	case CITY:
		cities.push_back(City(*((City*)p)));
		break;

	case ROAD:
		roads.push_back(Road(*((Road*)p)));
		break;

	default:
		break;
	}
}

void Board::DrawPieces()
{
	for (int i = 0; i < settlements.size(); i++)
	{
		settlements[i].Draw();
	}

	for (int i = 0; i < cities.size(); i++)
	{
		cities[i].Draw();
	}

	for (int i = 0; i < roads.size(); i++)
	{
		roads[i].Draw();
	}
}
