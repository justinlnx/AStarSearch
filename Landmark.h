#ifndef __LANDMARK_H__
#define __LANDMARK_H__
#include "GridCoordinate.h"
#include <vector>

class Landmark
{
public:
	Landmark();

	GridCoordinate GetNearestLandmark(GridCoordinate position) const;

	std::vector<GridCoordinate> GetPath(GridCoordinate sourceLandmark, GridCoordinate destLandmark) const;

private:
	// Given landmarks
	GridCoordinate landmark_a = GridCoordinate(5, 12);
	GridCoordinate landmark_b = GridCoordinate(12, 12);
	GridCoordinate landmark_c = GridCoordinate(5, 5);
	GridCoordinate landmark_d = GridCoordinate(12, 5);

	// private helper functions to get the path between landmarks
	static std::vector<GridCoordinate> GetPath_ab();
	static std::vector<GridCoordinate> GetPath_ac();
	static std::vector<GridCoordinate> GetPath_ad();
	static std::vector<GridCoordinate> GetPath_ba();
	static std::vector<GridCoordinate> GetPath_bc();
	static std::vector<GridCoordinate> GetPath_bd();
	static std::vector<GridCoordinate> GetPath_ca();
	static std::vector<GridCoordinate> GetPath_cb();
	static std::vector<GridCoordinate> GetPath_cd();
	static std::vector<GridCoordinate> GetPath_da();
	static std::vector<GridCoordinate> GetPath_db();
	static std::vector<GridCoordinate> GetPath_dc();
};

#endif
