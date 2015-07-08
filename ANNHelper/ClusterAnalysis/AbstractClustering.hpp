#pragma once

#ifndef _ABSTRACTCLUSTERING_H_
#define _ABSTRACTCLUSTERING_H_

// Library includes
#include <vector>
#include <list>

// Forward declarations
struct Cluster;
struct ValuePosition;

// This class contains all stuff needed to calculate clusters with the k-means cluster algorithm 
class AbstractClustering 
{
protected:
	// Sets the minimum cluster width
	static const float minClusterWidth;

	// Calculate the width of all given clusters based on their points
	void calculateAllClusterWidths(std::list<Cluster> &clusters);
	
	bool calculateClusterCentersFromMedians(std::list<Cluster> &clusters, bool withValue);
public:
	virtual ~AbstractClustering() {}

};

#endif