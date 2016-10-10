#ifndef __Node_H__
#define __Node_H__

#include "GridCoordinate.h"

struct Node
{
	int g; // cost from source to the current node
	int h; // estimated const from current node to destination
	int f; // total cost
	GridCoordinate position; // current position in the grid
	Node* parent;

	explicit Node(GridCoordinate& pos)
	{
		g = 0;
		h = 0;
		f = 0;
		position = pos;
		parent = nullptr;
	}

	int get_f() const
	{
		return g + h;
	}
};

#endif
