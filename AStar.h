#ifndef __ASTAR_H__
#define __ASTAR_H__

#include <vector>
#include "GridCoordinate.h"
#include "Node.h"

class AStar
{
public:
	AStar();
	~AStar();

	std::vector<GridCoordinate> Search(std::vector<Node*>* nodes, GridCoordinate source, GridCoordinate destination, int &frontierNodes);
private:
	static void CheckValidNeighbours(std::vector<Node*>* nodes, GridCoordinate& currentCoordinate, std::vector<GridCoordinate>& neighbourList);
	// determine the valid neighbours and append them to the neightbourList

	bool NeighbourInPriorityQueue(const GridCoordinate& neighbour, Node*& out);
	// determine whether this neighbour is already in the PriorityQueue

	int GetNodeIndex(Node* neighbourNode);
	// get the neighbour's index in entire nodes list

	void UpdatePriorityQueue(int hole);
	// update the Queue after updaing the costs

	std::vector<Node *> PriorityQueue;
	// private member variable PriorityQueue used to keep track of traversed nodes
};

#endif
