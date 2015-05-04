#pragma once

#ifndef _CLUSTER_H_
#define _CLUSTER_H_

// Library includes
#include <vector>

// This class contains all stuff needed to describe a Cluster 
struct Cluster
{
	std::vector<float> position;
	float width;
	int pointCount;
};

#endif