#include <vector>
#include <fstream>
#include "Node.h"
#include "GridCoordinate.h"
#include "AStar.h"
#include "Landmark.h"
#include <string>
#include <sstream>
using namespace std;

void InitializeGrid(ofstream* ouf, vector<Node*>* nodes)
{
	*ouf << "Initializing 18x18 Grid..." << endl;
	for (int y = 17; y >= 0; y--)
	{
		for (int x = 0; x < 18; x++)
		{
			GridCoordinate *position = new GridCoordinate;
			position->SetGrid(x, y);
			Node* node = new Node(*position);
			if (x == 7 && y >= 5 && y <= 9 || y == 13 && x >= 10 && x <= 15 || x == 15 && y == 12)
			{
				node->position.isBlocked = true;
				*ouf << "1, ";
			}
			else
			{
				*ouf << "0, ";
			}
			
			nodes->push_back(node);
			delete position;
		}
		*ouf << endl;
	}
	*ouf << endl;
}

void PrintPath(ofstream* ouf, vector<GridCoordinate> path)
{
	for (GridCoordinate position : path)
	{
		*ouf << "(" << position.x << ", " << position.y << ")" << endl;
	}
	*ouf << "This shortest path has length of " << path.size() << endl << endl;
}

GridCoordinate ReadInputValues(string readLine)
{
	int x;
	int y;
	int delimiter = readLine.find(",");
	int xValueLen = delimiter - 4;
	int yValueLen = readLine.size() - delimiter - 3;
	string xValue = readLine.substr(4, xValueLen);
	string yValue = readLine.substr(delimiter + 2, yValueLen);
	
	istringstream convert_x(xValue);
	convert_x >> x;
	istringstream convert_y(yValue);
	convert_y >> y;

	return GridCoordinate(x, y);
}

int main()
{
	ifstream inf("input.txt", ifstream::in);
	ofstream ouf("output.txt", ofstream::out);
	vector<Node*> *nodes = new vector<Node*>;

	InitializeGrid(&ouf, nodes);

	if (!inf)
	{
		ouf << "Input error! Unable to read the input file. Terminating program!" << endl;
		return 0;
	}

	string readLine;
	getline(inf, readLine);
	GridCoordinate source = ReadInputValues(readLine);
	getline(inf, readLine);
	GridCoordinate destination = ReadInputValues(readLine);

	vector<GridCoordinate> path;
	AStar* a_star = new AStar;

	ouf << "Computing shortest path from (" << source.x << ", " << source.y << ") to ("
		<< destination.x << ", " << destination.y << ")..." << endl;

	// -------------------------- Question 1 ----------------------------//
	// Compute the shortest path between two given points in the grid
	// Output the length of the path
	// Output the shortest path
	// Output the total number of nodes placed on the frontier, or the number of the nodes traversed
	ouf << endl << "Question 1 Compute the Shortest Path" << endl;
	int frontierNodes = 0; // number of nodes traverses in search, or placed on the frontier
	path = a_star->Search(nodes, source, destination, frontierNodes);
	PrintPath(&ouf, path);
	ouf << "The total number of nodes placed on frontier is: " << frontierNodes << endl;

	// -------------------------- Question 2 ----------------------------//
	// Compute the path between two points by passing through given nearest landmarks
	// Output the length of the path
	// Output the shortest path, path from source to landmark(s), landmark(s) to destination
	// Output the total number of nodes placed on the frontier, or the number of the nodes traversed
	ouf << endl << "Question 2 Compute the Shortest Path using Landmarks" << endl;

	Landmark* landmark = new Landmark;
	int f_sourceToLandmark = 0; // frontier nodes from source to nearest landmark
	int f_landmarkToDest = 0; // frontier nodes from landmark to destination
	GridCoordinate nearestLandmarkToSource;
	GridCoordinate nearestLandmarkToDest;
	vector<GridCoordinate> pathBetweenLandmarks;
	vector<GridCoordinate> pathFromSourceToLandmark;
	vector<GridCoordinate> pathFromLandmarkToDest;
	vector<GridCoordinate> combinedPath;
	
	// compute the three paths required
	// path from source to landmark
	// path from landmark to landmark
	// path from landmark to destination
	nearestLandmarkToSource = landmark->GetNearestLandmark(source);
	nearestLandmarkToDest = landmark->GetNearestLandmark(destination);
	pathBetweenLandmarks = landmark->GetPath(nearestLandmarkToSource, nearestLandmarkToDest);
	pathFromSourceToLandmark = a_star->Search(nodes, source, nearestLandmarkToSource, f_sourceToLandmark);
	pathFromLandmarkToDest = a_star->Search(nodes, nearestLandmarkToDest, destination, f_landmarkToDest);

	// combine the three path into one
	ouf << "Nearest Landmark to Source: (" << nearestLandmarkToSource.x << ", " << nearestLandmarkToSource.y << ") " << endl;
	ouf << "Nearest Landmark to Destination: (" << nearestLandmarkToDest.x << ", " << nearestLandmarkToDest.y << ") " << endl;
	combinedPath.reserve(pathBetweenLandmarks.size() + pathFromSourceToLandmark.size() + pathFromLandmarkToDest.size());
	combinedPath.insert(combinedPath.end(), pathFromSourceToLandmark.begin(), pathFromSourceToLandmark.end());
	combinedPath.insert(combinedPath.end(), pathBetweenLandmarks.begin(), pathBetweenLandmarks.end());
	combinedPath.insert(combinedPath.end(), pathFromLandmarkToDest.begin(), pathFromLandmarkToDest.end());

	PrintPath(&ouf, combinedPath);
	ouf << "The total number of nodes placed on frontier is: " << f_sourceToLandmark + f_landmarkToDest << endl;

	ouf.close();

	delete a_star;
	delete landmark;
	delete nodes;

	return 0;
}
