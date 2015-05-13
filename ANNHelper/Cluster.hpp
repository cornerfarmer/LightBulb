#pragma once

#ifndef _CLUSTER_H_
#define _CLUSTER_H_

// Library includes
#include <vector>
#include <list>

// Includes
#include "Point.hpp"

// This class contains all stuff needed to describe a Cluster 
struct Cluster
{
	// The position of the cluster
	Point position;
	// All points contained by the cluster
	std::list<Point*> points;
	// The radius of the cluster
	float radius;
	Cluster()
	{
		radius = 0;
	}
	Cluster(Point &position_, float radius_)
	{
		position = position_;
		radius = radius_;
	}
};

#endif