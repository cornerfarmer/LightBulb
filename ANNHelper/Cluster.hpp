#pragma once

#ifndef _CLUSTER_H_
#define _CLUSTER_H_

// Library includes
#include <vector>
#include <list>

// Forward declarations
struct Point;

// This class contains all stuff needed to describe a Cluster 
struct Cluster
{
	// The position of the cluster
	std::vector<float> position;
	// All points contained by the cluster
	std::list<Point*> points;
	// The radius of the cluster
	float radius;
};

#endif