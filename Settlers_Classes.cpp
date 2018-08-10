#include "Settlers_Classes.h"

Node::Node()
{
	num_regions = 0;
	num_neighbors = 0;
	nodeID = 0;
	value = 0;
	future_value = 0;
	region_list = NULL; //initalizes an empty int array of size regions
	neighbor_list = NULL; //initalizes an empty int array of size neighbors
	owner = NO_PLAYER;
}

void Node::printNode()
{
	int * regionList = get_region_list();
	int * neighborList = get_neighbor_list();
	std::cout << "Regions: ";
	for (int i = 0; i < num_regions; i++) std::cout << *(regionList + i) << ", ";
	std::cout << "\n";
	std::cout << "Neighbors: ";
	for (int i = 0; i < num_neighbors; i++) std::cout << *(neighborList + i) << ",";
	std::cout << "\n";
	std::cout << "Value: " << value;
}

Node::~Node()
{
	if(region_list != NULL) delete[] region_list;
	if(neighbor_list != NULL) delete[] neighbor_list;
}

int* Node::get_region_list() { return region_list; }
int Node::get_num_regions() { return num_regions; }
int* Node::get_neighbor_list() { return neighbor_list; }
int Node::get_num_neighbors() { return num_neighbors; }

void Node::set_region_list(int * regions, int regsNum)
{
	delete[] region_list;
	num_regions = regsNum;
	region_list = copy_list(regsNum, regions);
}

void Node::set_neighbor_list(int * neighbors, int neighborsNum)
{
	delete[] neighbor_list;
	num_neighbors = neighborsNum;
	neighbor_list = copy_list(neighborsNum, neighbors);
}

player Node::get_owner() { return owner; }
void Node::set_owner(player new_owner) { owner = new_owner; }
void Node::set_value(double new_val) { value = new_val; }
double Node::get_value() { return value; }
void Node::set_future_value(double new_val) { future_value = new_val; }
double Node::get_future_value() { return future_value; }
void Node::set_nodeID(int new_val) { nodeID = new_val; }
int Node::get_nodeID() { return nodeID; }

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
	int *rptr = new int[3];
	int *nptr = new int[3];
	int node_count = 0;

	FILE *f = fopen("hashtable.txt", "rb");
	if (f == NULL) {
		std::cout << "Could Not Open File";
	}
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
			nodes[node_count].set_nodeID(node_count);
			if (DEBUG) {
				std::cout << "\n**** NODE: " << node_count << " ****\n";
				nodes[node_count].printNode();
			}
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
			nodes[node_count].set_nodeID(node_count);
			if (DEBUG) {
				std::cout << "\n**** NODE: " << node_count << " ****\n";
				nodes[node_count].printNode();
			}
			nrows = 0;
			rrows = 0;
			neighbors = true;
			val = 0;
			node_count++;
		}
	}
	delete[] nptr;
	delete[] rptr;
	updateFutureValues();
	//rank the nodes
	rankNodes();
	//display the best node (note there are probably a couple best options)
	if(DEBUG) std::cout << "\n\n Best Node: " << get_best_open_node() << "\n";
}

void Board::rankNodes()
{
	for (int i = 0; i < 54; i++) nodeRank[i] = i;
	node_insertionSort(nodeRank, (sizeof(nodeRank) / sizeof(nodeRank[0])));
	if (DEBUG) {
		std::cout << "\n-----\nNode Ranks: ";
		for (int i = 0; i < 54; i++) std::cout << nodeRank[i] << ", ";
	}
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

int Board::get_region_number(int region) { return regions[region]; }

void Board::printWelcome()
{
	std::cout << "Welcome";
}


void Board::updateFutureValues() {
	for (int i = 0; i < 54; i++) {
		updateFutureValue(i);
	}
}
void Board::updateFutureValue(int nodeID) {
	int * immediateNeighbors = nodes[nodeID].get_neighbor_list();
	int immediateNeighborsNum = nodes[nodeID].get_num_neighbors();
	int *tempNeighbors = NULL;
	int tempNeighborsNum = 0;
	double next_future_value = 0;
	for (int i = 0; i < immediateNeighborsNum; i++)
	{
		if (nodes[*immediateNeighbors + i].get_owner() == NO_PLAYER) {
			tempNeighbors = nodes[*immediateNeighbors + i].get_neighbor_list();
			tempNeighborsNum = nodes[*immediateNeighbors + i].get_num_neighbors();
			for (int j = 0; j < tempNeighborsNum; j++) {
				if (nodes[*immediateNeighbors + i].get_owner() == NO_PLAYER && nodes[*immediateNeighbors + i].get_nodeID() != nodeID) {
					next_future_value += nodes[*immediateNeighbors + i].get_value();
				}
			}
		}
			
	}
	if(DEBUG) std::cout << "\n Node " << nodeID << " future value is: " << next_future_value;
	nodes[nodeID].set_future_value(next_future_value);
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

int * copy_list(int size, int* list) {
	int* returnptr = new int[size];
	for (int i = 0; i < size; i++) {
		*(returnptr + i) = *(list + i);
	}
	return returnptr;
}
