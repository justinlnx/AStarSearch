#include "AStar.h"
#include "GridCoordinate.h"
#include <cassert>
#include "Node.h"
#include <algorithm>
#include <iterator>

AStar::AStar()
{
}

AStar::~AStar()
{
	PriorityQueue.clear();
}

void AStar::CheckValidNeighbours(std::vector<Node*>* nodes, GridCoordinate& currentCoordinate, std::vector<GridCoordinate>& neighbourList)
{
	// Check the current node's 4 neighbours, top, left, bottom and right
	// if the neighbour is blocked, skip to the next node
	// if the neighbour is okay to pass, append it to the neighbourList
	neighbourList.clear();

	GridCoordinate top;
	GridCoordinate bot;
	GridCoordinate left;
	GridCoordinate right;
	int top_y = currentCoordinate.y + 1;
	int right_x = currentCoordinate.x + 1;
	int bot_y = currentCoordinate.y - 1;
	int left_x = currentCoordinate.x - 1;

	// reset the max and min value allowed for x,y cooridnates
	if (top_y > 17) top_y = 17;
	if (right_x > 17) right_x = 17;
	if (bot_y < 0) bot_y = 0;
	if (left_x < 0) left_x = 0;

	// set neighbours position
	top.SetGrid(currentCoordinate.x, top_y);
	bot.SetGrid(currentCoordinate.x, bot_y);
	left.SetGrid(left_x, currentCoordinate.y);
	right.SetGrid(right_x, currentCoordinate.y);

	for (std::vector<Node*>::iterator i = nodes->begin(); i != nodes->end(); i++)
	{
		Node* ithNode = nodes->at(std::distance(nodes->begin(), i));
		// find the iThNode from the beginning of the node list, and compare it with the current neightbourNode

		if (ithNode->position.isBlocked) continue;

		if (ithNode->position.IsEqualTo(top) && !top.IsEqualTo(currentCoordinate))
		{
			// push valid top neighbour to the list
			neighbourList.push_back(top);
		}

		if (ithNode->position.IsEqualTo(bot) && !bot.IsEqualTo(currentCoordinate))
		{
			// push valid bot neighbour to the list
			neighbourList.push_back(bot);
		}

		if (ithNode->position.IsEqualTo(left) && !left.IsEqualTo(currentCoordinate))
		{
			// push valid left neighbour to the list
			neighbourList.push_back(left);
		}

		if (ithNode->position.IsEqualTo(right) && !right.IsEqualTo(currentCoordinate))
		{
			// push valid right neighbour to the list
			neighbourList.push_back(right);
		}
	}
}

bool AStar::NeighbourInPriorityQueue(const GridCoordinate& neighbour, Node*& out)
{
	for (std::vector<Node*>::iterator i = PriorityQueue.begin(); i != PriorityQueue.end(); i++)
	{
		Node* index = PriorityQueue.at(std::distance(PriorityQueue.begin(), i));
		// find the iThNode in the PriorityQueue
		if (index->position.IsEqualTo(neighbour))
		{
			// return this node to out
			out = index;
			return true;
		}
	}
	return false;
}

int AStar::GetNodeIndex(Node* neighbourNode)
{
	int index = 0;
	const int size = PriorityQueue.size();
	while (index < size)
	{
		if (PriorityQueue[index]->position.IsEqualTo(neighbourNode->position))
		{
			return index;
		}
		++index;
	}
	return index;
}

void AStar::UpdatePriorityQueue(int nodeIndex)
{
	int parentIndex;
	while (nodeIndex > 0)
	{
		parentIndex = (nodeIndex - 1) / 2;
		if (PriorityQueue[nodeIndex]->get_f() < PriorityQueue[parentIndex]->get_f())
		{
			std::swap(PriorityQueue[nodeIndex], PriorityQueue[parentIndex]);
			nodeIndex = parentIndex;
		}
		else
		{
			return;
		}
	}
}

std::vector<GridCoordinate> AStar::Search(std::vector<Node*>* nodes, GridCoordinate source, GridCoordinate destination, int &frontierNodes)
{
	std::vector<GridCoordinate> path;
	std::vector<GridCoordinate> neighbour_nodes;
	neighbour_nodes.reserve(4); // each node has four neightbours

	Node* start_node = new Node(source);
	PriorityQueue.push_back(start_node);

	bool foundPath = false;
	while (!PriorityQueue.empty())
	{
		Node* current_node = *PriorityQueue.begin();
		std::pop_heap(PriorityQueue.begin(), PriorityQueue.end(), [](const Node* a, const Node* b)-> bool
		              {
			              return a->get_f() > b->get_f();
		              });
		PriorityQueue.pop_back();

		// set the neighbourNodes
		CheckValidNeighbours(nodes, current_node->position, neighbour_nodes);
		
		// increment the frontierNodes
		// Currently at this node, it has neighbour_nodes.size() of nodes, add this number of the frontierNodes
		frontierNodes += neighbour_nodes.size(); 

		// find the currentNode's neighbour that has the minimum costs
		for (GridCoordinate neighbourPosition : neighbour_nodes)
		{
			Node* neighbourNode = nullptr;

			if (NeighbourInPriorityQueue(neighbourPosition, neighbourNode))
			{
				// if node is already in the PriorityQueue, update neighbour's info if possible
				int g_value = current_node->g + 1;
				if (g_value < neighbourNode->g)
				{
					neighbourNode->g = g_value; // update the g cost
					neighbourNode->parent = current_node; // set the parent of this neighbour to current node

					int index;
					index = GetNodeIndex(neighbourNode);
					UpdatePriorityQueue(index); // update the PriorityQueue
				}
			}
			else
			{
				// neighbourNode has not yet been appended to PriorityQueue yet
				// create a new node and append it to PriorityQueue
				neighbourNode = new Node(neighbourPosition);

				neighbourNode->parent = current_node;
				neighbourNode->h = abs(destination.y + destination.x - neighbourNode->position.y - neighbourNode->position.x);
				neighbourNode->g = current_node->g + 1;

				PriorityQueue.push_back(neighbourNode);
				std::push_heap(PriorityQueue.begin(), PriorityQueue.end(), [](const Node* a, const Node* b)-> bool
				               {
					               return a->get_f() > b->get_f();
				               });

				// now check if this reaches destination yet
				if (neighbourPosition.IsEqualTo(destination))
				{
					while (neighbourNode->parent)
					{
						path.push_back(neighbourNode->position);
						neighbourNode = neighbourNode->parent;
					}
					reverse(path.begin(), path.end());
					foundPath = true;
					break;
				}
			}
		}

		if (foundPath) break;
	}

	PriorityQueue.clear();
	return path;
}
