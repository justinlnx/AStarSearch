#include "GridCoordinate.h"
#include <cassert>
#include <iterator>
#include "Landmark.h"

Landmark::Landmark()
{
}

GridCoordinate Landmark::GetNearestLandmark(GridCoordinate position) const
{
	// return the nearest landmark from given position
	// by calculating the estimated costs from landmark to given position
	int to_a = abs(landmark_a.y + landmark_a.x - position.y - position.x);
	int to_b = abs(landmark_b.y + landmark_b.x - position.y - position.x);
	int to_c = abs(landmark_c.y + landmark_c.x - position.y - position.x);
	int to_d = abs(landmark_d.y + landmark_d.x - position.y - position.x);
	int list[4] = {to_a, to_b, to_c, to_d};
	int min = INT_MAX;
	for (int value : list)
	{
		if (value < min)
		{
			min = value;
		}
	}

	if (min == to_a) return landmark_a;
	if (min == to_b) return landmark_b;
	if (min == to_c) return landmark_c;
	return landmark_d;
}

std::vector<GridCoordinate> Landmark::GetPath(GridCoordinate sourceLandmark, GridCoordinate destLandmark) const
{
	// return the path between two landmarks
	// first find out which two landmarks are concerned, then compute the path
	std::vector<GridCoordinate> path;
	if (sourceLandmark.IsEqualTo(landmark_a) && destLandmark.IsEqualTo(landmark_b)) path = GetPath_ab();
	if (sourceLandmark.IsEqualTo(landmark_a) && destLandmark.IsEqualTo(landmark_c)) path = GetPath_ac();
	if (sourceLandmark.IsEqualTo(landmark_a) && destLandmark.IsEqualTo(landmark_d)) path = GetPath_ad();
	if (sourceLandmark.IsEqualTo(landmark_b) && destLandmark.IsEqualTo(landmark_a)) path = GetPath_ba();
	if (sourceLandmark.IsEqualTo(landmark_b) && destLandmark.IsEqualTo(landmark_c)) path = GetPath_bc();
	if (sourceLandmark.IsEqualTo(landmark_b) && destLandmark.IsEqualTo(landmark_d)) path = GetPath_bd();
	if (sourceLandmark.IsEqualTo(landmark_c) && destLandmark.IsEqualTo(landmark_a)) path = GetPath_ca();
	if (sourceLandmark.IsEqualTo(landmark_c) && destLandmark.IsEqualTo(landmark_b)) path = GetPath_cb();
	if (sourceLandmark.IsEqualTo(landmark_c) && destLandmark.IsEqualTo(landmark_d)) path = GetPath_cd();
	if (sourceLandmark.IsEqualTo(landmark_d) && destLandmark.IsEqualTo(landmark_a)) path = GetPath_da();
	if (sourceLandmark.IsEqualTo(landmark_d) && destLandmark.IsEqualTo(landmark_b)) path = GetPath_db();
	if (sourceLandmark.IsEqualTo(landmark_d) && destLandmark.IsEqualTo(landmark_c)) path = GetPath_dc();

	return path;
}


std::vector<GridCoordinate> Landmark::GetPath_ab()
{
	std::vector<GridCoordinate> path;
	for (int x = 6; x <= 12; x++)
	{
		GridCoordinate position;
		position.SetGrid(x, 12);
		path.push_back(position);
	}
	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_ac()
{
	std::vector<GridCoordinate> path;
	for (int y = 11; y >= 5; y--)
	{
		GridCoordinate position;
		position.SetGrid(5, y);
		path.push_back(position);
	}
	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_ad()
{
	std::vector<GridCoordinate> pathab;
	std::vector<GridCoordinate> pathbd;
	std::vector<GridCoordinate> path;
	pathab = GetPath_ab();
	pathbd = GetPath_bd();
	path.reserve(pathab.size() + pathbd.size());
	path.insert(path.end(), pathab.begin(), pathab.end());
	path.insert(path.end(), pathbd.begin(), pathbd.end());

	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_ba()
{
	std::vector<GridCoordinate> path;
	path = GetPath_ab();
	reverse(path.begin(), path.end());
	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_bc()
{
	std::vector<GridCoordinate> pathba;
	std::vector<GridCoordinate> pathac;
	std::vector<GridCoordinate> path;
	pathba = GetPath_ba();
	pathac = GetPath_ac();
	path.reserve(pathba.size() + pathac.size());
	path.insert(path.end(), pathba.begin(), pathba.end());
	path.insert(path.end(), pathac.begin(), pathac.end());

	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_bd()
{
	std::vector<GridCoordinate> path;
	for (int y = 11; y >= 5; y--)
	{
		GridCoordinate position;
		position.SetGrid(12, y);
		path.push_back(position);
	}
	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_ca()
{
	std::vector<GridCoordinate> path;
	path = GetPath_ac();
	reverse(path.begin(), path.end());
	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_cb()
{
	std::vector<GridCoordinate> path;
	path = GetPath_bc();
	reverse(path.begin(), path.end());
	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_cd()
{
	std::vector<GridCoordinate> path;
	for (int x = 5; x <= 12; x++)
	{
		GridCoordinate position;
		position.SetGrid(x, 5);
		path.push_back(position);
	}
	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_da()
{
	std::vector<GridCoordinate> path;
	path = GetPath_ad();
	reverse(path.begin(), path.end());
	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_db()
{
	std::vector<GridCoordinate> path;
	path = GetPath_bd();
	reverse(path.begin(), path.end());
	return path;
}

std::vector<GridCoordinate> Landmark::GetPath_dc()
{
	std::vector<GridCoordinate> path;
	path = GetPath_cd();
	reverse(path.begin(), path.end());
	return path;
}
