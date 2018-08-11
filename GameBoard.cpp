#include <algorithm>
#include <time.h>
#include "GameBoard.h"

GameBoard::GameBoard()
{
	
}

void GameBoard::SetBoard(Board * board)
{
	this->settlements.clear();
	this->cities.clear();
	this->roads.clear();

	this->board = board;

	// mapping from Board class structure to GameBoard Structure
	const int map[19] = { 0,1,2,6,11,15,18,17,16,12,7,3,4,5,10,14,13,8,9 };

	// Set up the tile location, region type, and number
	for (int i = 0; i < NUM_REGIONS; i++)
	{
		tiles[i].location = hexes[i];

		resource_type resource = board->get_region_type(i);
		
		switch (resource)
		{
		case WOOD:
			tiles[map[i]].type = Forest;
			break;
		case BRICK:
			tiles[map[i]].type = Hills;
			break;
		case STONE:
			tiles[map[i]].type = Mountains;
			break;
		case WHEAT:
			tiles[map[i]].type = Fields;
			break;
		case SHEEP:
			tiles[map[i]].type = Pasture;
			break;
		case BARREN:
			tiles[map[i]].type = Desert;
			break;
		default:
			tiles[map[i]].type = None;
			break;
		}

		tiles[map[i]].number = board->get_roll_number(i);

		if (tiles[map[i]].number == 0)
			tiles[map[i]].number = 7;
	}
}

void GameBoard::DrawBoard()
{
	for (int i = 0; i < 19; i++)
	{
		tiles[i].Draw();
	}
}

void GameBoard::AddPiece(Piece * p)
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

void GameBoard::DrawPieces()
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
