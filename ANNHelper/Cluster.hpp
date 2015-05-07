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
	std::vector<float> position;
	std::list<Point*> points;
	float width;
};

#endif