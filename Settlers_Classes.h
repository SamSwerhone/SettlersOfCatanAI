//Settler_Classes.h

#define _CRT_SECURE_NO_DEPRECATE

#define DEBUG 1

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

#define NUM_REGIONS 19
#define NUM_NODES 54
#define BARREN_REGION 18
#define FUTURE_REGION_WEIGHT 0.25

//These are the colors that correspond to players
typedef enum player
{
	NO_PLAYER = 0,
	RED = 1,
	YELLOW = 2,
	BLUE = 3,
	WHITE = 4
};

//These are the type of regions or hexgions
typedef enum resource_type
{
	NONE = 0,
	WOOD = 1,
	BRICK = 2,
	STONE = 3,
	WHEAT = 4,
	SHEEP = 5,
	BARREN = 6
};

double cast_region_to_prob(int region); //helper function which maps region to actual probability
int * copy_list(int size, int* list); //helper function for ensureing deep ptr array copies

//This class is the atomic nodes which can players place houses/cities on
class Node
{
	public:
		Node();
		~Node();
		int* get_region_list(); //returns a pointer to all the regions this node occupies
		int get_num_regions(); //returns the number of regions this node occupies
		void set_region_list(int * regions, int regsNum); //called only during instantiation
		int* get_neighbor_list(); //returns a pointer to all the neighboring nodes
		int get_num_neighbors(); //returns the number of neighboring nodes
		void set_neighbor_list(int * neighbors, int neighborsNum); //called only during instantiation
		player get_owner(); //returns the owner (NO_PLAYER, RED, YELLOW, BLUE, WHITE)
		void set_owner(player new_owner); //sets the owner, should only be called once per game
		void set_value(double new_val); //sets the value of this specific node bases on regions occupied
		double get_value(); //returns the value, a number between 0 and 1;
		void set_future_value(double new_val);
		double get_future_value();
		int get_nodeID();
		void set_nodeID(int id);
		void printNode(); //used for debugging, prints this nodes regions and neighbors
	private:
		int* region_list; //list of all regions occupied
		int* neighbor_list; //list of all neighboring nodes
		int num_regions;
		int num_neighbors;
		int nodeID;
		double value; //based on probability of regions, and the neighbor's neighbor's regions
		double future_value; //based on the value of non_owned neighbor's neighbor's values
		player owner;
};

class Board
{
	public:
		void printWelcome();//used for debugging
		void rankNodes(); //ranks nodes based on their regions/probabilities (may be extended)
		void updateFutureValues();
		void updateFutureValue(int nodeID);
		bool ownNode(player new_owner, int node); //set the passed in node's owner to the passed in player
		int get_best_open_node(); //returns the best unoccupied node
		resource_type get_region_type(int region); //returns the region type of the specified hexegon
		int get_region_number(int region); //returns the region value of the specified hexegon
		int get_roll_number(int region); //returns the regions associated dice roll number
		double get_region_probability(int region); //returns the region probability of the specified hexegon
		Board(); //sets up the entire game, randomly under game criteria
	private:
		Node nodes[54]; //contains all the nodes in the order specified in numbering_scheme.jpg
		int nodeRank[54]; //a seperate array which sorts nodes by rank
		resource_type region_resource[NUM_REGIONS]; //a seperate array which contains each region type
		void node_insertionSort(int arr[], int n); //used to sort the nodes based on probabilities 
		int regions[NUM_REGIONS]; //contains all the regions (also known as hexagons)
};
