#pragma once

#ifndef _ABSTRACTCLUSTERING_H_
#define _ABSTRACTCLUSTERING_H_

// Library includes
#include <vector>
#include <list>

// Forward declarations
struct Cluster;
struct Point;

// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
class AbstractClustering 
{
protected:
	// Sets the minimum cluster width
	static const float minClusterWidth;
	// Calculates the (value and position) distance between two points
	float getDistanceBetweenPoints(Point &point1, Point &point2);
	// Calculates the distance between two positions
	float getDistanceBetweenPositions(std::vector<float> &pos1, std::vector<float> &pos2);
	// Calculate the width of all given clusters based on their points
	void calculateAllClusterWidths(std::list<Cluster> &clusters);
public:
	virtual ~AbstractClustering() {}

};

#endif