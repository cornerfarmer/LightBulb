#pragma once

#ifndef _CLUSTER_H_
#define _CLUSTER_H_

// Library includes
#include <vector>
#include <list>

// Includes
#include "ClusterAnalysis\ValuePosition.hpp"
#include "ClusterAnalysis\PointSet.hpp"

// Forward declaration
struct Point;

// This class contains all stuff needed to describe a Cluster 
struct Cluster
{
	// The position of the cluster
	ValuePosition center;
	// All points contained by the cluster
	PointSet points;
	// The radius of the cluster
	double radius;
	Cluster()
	{
		radius = 0;
	}
	Cluster(ValuePosition &center_, double radius_)
	{
		center = center_;
		radius = radius_;
	}
};

#endif