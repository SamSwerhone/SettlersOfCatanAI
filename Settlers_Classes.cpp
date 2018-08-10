#define _CRT_SECURE_NO_DEPRECATE

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

#define NUM_REGIONS 19
#define BARREN_REGION 18

typedef enum player
{
	NO_PLAYER = 0,
	RED = 1,
	YELLOW = 2,
	BLUE = 3,
	WHITE = 4
};

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

double cast_region_to_prob(int region);

class Node
{
public:
	Node();
	Node(int regions, int neighbors);
	Node(int regions, int neighbors, int* regions_array, int* neighbors_array);
	~Node();
	int* get_region_list();
	int get_num_regions();
	void set_region_list(int * regions, int regsNum);
	int* get_neighbor_list();
	int get_num_neighbors();
	void set_neighbor_list(int * neighbors, int neighborsNum);
	player get_owner();
	void set_owner(player new_owner);
	void set_value(double new_val);
	double get_value();
	void printNode();
private:
	int* region_list;
	int* neighbor_list;
	int num_regions;
	int num_neighbors;
	double value; //based on probability of regions, and the neighbor's neighbor's regions
	player owner;
};

Node::Node()
{
	num_regions = 0;
	num_neighbors = 0;
	value = 0;
	region_list = NULL; //initalizes an empty int array of size regions
	neighbor_list = NULL; //initalizes an empty int array of size neighbors
	owner = NO_PLAYER;
}

void Node::printNode()
{
	int * regionList = get_region_list();
	int * neighborList = get_neighbor_list();
	cout << "Regions: ";
	for (int i = 0; i < num_regions; i++) cout << *(regionList + i) << ", ";
	cout << "\n";
	cout << "Neighbors: ";
	for (int i = 0; i < num_neighbors; i++) cout << *(neighborList + i) << ",";
	cout << "\n";
	//cout << "Value: " << value;
}

Node::Node(int regions, int neighbors)
{
	value = 0;
	num_regions = regions;
	num_neighbors = neighbors;
	region_list = new int[regions](); //initalizes an empty int array of size regions
	neighbor_list = new int[neighbors](); //initalizes an empty int array of size neighbors
	owner = NO_PLAYER;
}

Node::Node(int regions, int neighbors, int* regions_array, int* neighbors_array)
{
	value = 0;
	num_regions = regions;
	num_neighbors = neighbors;
	region_list = new int[regions](); //initalizes an empty int array of size regions
	neighbor_list = new int[neighbors](); //initalizes an empty int array of size neighbors
	owner = NO_PLAYER;
	for (int i = 0; i < num_regions; i++) region_list[i] = regions_array[i];
	for (int i = 0; i < num_neighbors; i++) neighbor_list[i] = neighbors_array[i];
}

Node::~Node()
{
	delete[] region_list;
	delete[] neighbor_list;
}

int* Node::get_region_list() { return region_list; }
int Node::get_num_regions() { return num_regions; }
int* Node::get_neighbor_list() { return neighbor_list; }
int Node::get_num_neighbors() { return num_neighbors; }

void Node::set_region_list(int * regions, int regsNum)
{
	delete[] region_list;
	num_regions = regsNum;
	region_list = new int[regsNum](); //initalizes an empty int array of size regions
	for (int i = 0; i < regsNum; i++) region_list[i] = regions[i];
}

void Node::set_neighbor_list(int * neighbors, int neighborsNum)
{
	delete[] neighbor_list;
	num_neighbors = neighborsNum;
	neighbor_list = new int[neighborsNum](); //initalizes an empty int array of size regions
	for (int i = 0; i < neighborsNum; i++) neighbor_list[i] = neighbors[i];
}

player Node::get_owner() { return owner; }
void Node::set_owner(player new_owner) { owner = new_owner; }
void Node::set_value(double new_val) { value = new_val; }
double Node::get_value() { return value; }

class Board
{
public:
	void printWelcome();
	void rankNodes();
	bool ownNode(player new_owner, int node);
	int get_best_open_node();
	resource_type get_region_type(int region);
	double get_region_probability(int region);
	Board();
private:
	Node nodes[54];
	int nodeRank[54];
	resource_type region_resource[NUM_REGIONS];
	void node_quickSort(int arr[], int left, int right);
	void node_insertionSort(int arr[], int n);
	int regions[NUM_REGIONS];
};

Board::Board()
{
	std::fstream myfile("hashtable.txt", std::ios_base::in);
	//Node(int regions, int neighbors, int* regions_array, int* neighbors_array);

	//first set all the region probabilities, pseudo randomly;
	//First a random starting coastal region, then lay down numbers (remember the array order is starting
	//at the top left corner and spiraling in, but the A-S ints can vary and those determine the probability
	int random_start;
	srand(time(NULL));
	random_start = rand() % NUM_REGIONS;
	// this will map the values; but use cast_region_to_prob(region[i]) to get prob for each region
	for (int i = 0; i < NUM_REGIONS; i++)
	{
		region_resource[i] = NONE;
		regions[i] = ((random_start + i) % NUM_REGIONS);
		if (regions[i] == 18) region_resource[i] = BARREN;
	}
	int numWOOD = 4;
	int	numBRICK = 3;
	int	numSTONE = 3;
	int	numWHEAT = 4;
	int numSHEEP = 4;
	//randomly assign regions, probably  a more efficient way to do this
	for (int i = 0; i < NUM_REGIONS; i=i)
	{
		random_start = (rand() % 5) + 1;
		if (region_resource[i] == BARREN) {
			//do nothing
			i++;
		}
		else if (random_start == WOOD && numWOOD > 0) {
			region_resource[i++] = WOOD;
			numWOOD--;
		}
		else if (random_start == BRICK && numBRICK > 0) {
			region_resource[i++] = BRICK;
			numBRICK--;
		}
		else if (random_start == STONE && numSTONE > 0) {
			region_resource[i++] = STONE;
			numSTONE--;
		}
		else if (random_start == WHEAT && numWHEAT > 0) {
			region_resource[i++] = WHEAT;
			numWHEAT--;
		}
		else if (random_start == SHEEP && numSHEEP > 0) {
			region_resource[i++] = SHEEP;
			numSHEEP--;
		}
	}

	int i = 0;
	int nrows = 0;
	int rrows = 0;
	bool neighbors = true;
	char c = 'Z';
	int val = 0;
	int *rptr = (int *)malloc(3);
	int *nptr = (int *)malloc(3);
	int node_count = 0;

	FILE *f = fopen("hashtable.txt", "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *string = (char *)malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);

	string[fsize] = '\0';

	//use hashtable to determine the node's regions and neighbors
	//also maybe a better way to do this, but i just used , and ; as deliminators
	while (c != '\0')
	{
		c = string[i];
		if (c == '\r') {}
		else if (c == '\n') // reset counters and arrays
		{
			double reg_val = 0;
			nodes[node_count].set_region_list(rptr, rrows);
			for (int k = 0; k < rrows; k++) reg_val = reg_val + cast_region_to_prob(regions[*(rptr + k)]);
			nodes[node_count].set_value(reg_val);
			nodes[node_count].set_neighbor_list(nptr, nrows);
			cout << "\n**** NODE: " << node_count << " ****\n";
			nodes[node_count].printNode();
			nrows = 0;
			rrows = 0;
			neighbors = true;
			val = 0;
			i++;
			node_count++;
		}
		else if (c == ';') //add value to array, switch to second array
		{
			if (neighbors) {
				*(nptr + nrows) = val;
				nrows++;
			}
			else
			{
				*(rptr + rrows) = val;
				rrows++;
			}
			neighbors = !neighbors;
			val = 0;
			i++;
		}
		else if (c == ',') //add value to array switch to new element in array
		{
			if (neighbors) {
				*(nptr + nrows) = val;
				nrows++;
			}
			else
			{
				*(rptr + rrows) = val;
				rrows++;
			}
			val = 0;
			i++;
		}
		else if (c != '\0') //add to value
		{
			val = val * 10 + (c - '0');
			i++;
		}
		else if (c == '\0')
		{
			double reg_val = 0;
			nodes[node_count].set_region_list(rptr, rrows);
			for (int k = 0; k < rrows; k++) reg_val = reg_val + cast_region_to_prob(regions[*(rptr + k)]);
			nodes[node_count].set_value(reg_val);
			nodes[node_count].set_neighbor_list(nptr, nrows);
			cout << "\n**** NODE: " << node_count << " ****\n";
			nodes[node_count].printNode();
			nrows = 0;
			rrows = 0;
			neighbors = true;
			val = 0;
			node_count++;
		}
	}
	//rank the nodes
	rankNodes();
	//display the best node (note there are probably a couple best options)
	cout << "\n\n Best Node: " << get_best_open_node() << "\n";
}

void Board::rankNodes()
{
	for (int i = 0; i < 54; i++) nodeRank[i] = i;
	node_insertionSort(nodeRank, (sizeof(nodeRank) / sizeof(nodeRank[0])));
	cout << "\n-----\nNode Ranks: ";
	for (int i = 0; i < 54; i++) cout << nodeRank[i] << ", ";
}

void Board::node_quickSort(int arr[], int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = nodes[arr[(left + right) / 2]].get_value();
	/* partition */
	while (i <= j) {
		while (nodes[arr[i]].get_value() < pivot)
			i++;
		while (nodes[arr[j]].get_value() > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};
	/* recursion */
	if (left < j)
		node_quickSort(arr, left, j);
	if (i < right)
		node_quickSort(arr, i, right);
}

void Board::node_insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && nodes[arr[j]].get_value() > nodes[key].get_value())
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

bool Board::ownNode(player new_owner, int node)
{
	if (nodes[node].get_owner() == NO_PLAYER)
	{
		nodes[node].set_owner(new_owner);
		return true;
	}
	else return false;
}

int Board::get_best_open_node()
{
	bool open = false;
	for (int i = 53; i >= 0; i--)
	{
		if (nodes[nodeRank[i]].get_owner() == NO_PLAYER) return nodeRank[i];
	}
	return -1;
}

void Board::printWelcome()
{
	cout << "Welcome";
}

resource_type Board::get_region_type(int region) { return region_resource[region]; }
double Board::get_region_probability(int region) { return cast_region_to_prob(region); } 

double cast_region_to_prob(int region)
{
	if (region == 2 || region == 15 || region == 4 || region == 10) return 0.13889;//prob rolling 6, 10;
	else if (region == 0 || region == 14 || region == 6 || region == 12) return 0.11111;//prob rolling 5 , 9;
	else if (region == 9 || region == 13 || region == 11 || region == 5) return 0.08333;//prob rolling 4, 10;
	else if (region == 3 || region == 16 || region == 8 || region == 17) return 0.05556;//prob rolling 3, 11;
	else if (region == 1 || region == 7) return 0.02778; //prob rolling 2, 12;
	else if (region == 18) return 0;//prob rolling barren (7), actual prob is 0.16667
}

int main() {

	// Declare an object of class geeks
	Board obj1;

	// accessing member function
	obj1.printWelcome();
	while (1);
	return 0;
}
