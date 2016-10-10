#ifndef __GRIDCOORDINATE_H__
#define __GRIDCOORDINATE_H__

struct GridCoordinate
{
	int x;
	int y;
	bool isBlocked;

	GridCoordinate()
	{
		x = 0;
		y = 0;
		isBlocked = false;
	}

	GridCoordinate(int x_value, int y_value)
	{
		x = x_value;
		y = y_value;
		isBlocked = false;
	}

	void SetGrid(int x_value, int y_value)
	{
		x = x_value;
		y = y_value;
		isBlocked = false;
	}

	bool IsEqualTo(GridCoordinate gridCoordinate) const
	{
		return x == gridCoordinate.x && y == gridCoordinate.y;
	}
};

#endif
