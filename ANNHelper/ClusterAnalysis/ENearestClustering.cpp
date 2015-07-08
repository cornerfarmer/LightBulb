#include "ClusterAnalysis\ENearestClustering.hpp"
#include "ClusterAnalysis\Cluster.hpp"
#include <algorithm>
#include "ClusterAnalysis\Point.hpp"
#include "ClusterAnalysis\PointSet.hpp"

void ENearestClustering::calculateCache(PointSet& points)
{
	// Go through all points
	for (PointSet::iterator fromPoint = points.begin(); fromPoint != points.end(); fromPoint++)
	{
		// Bring the point list of the current point to the right size
		distanceToPoint[*fromPoint].resize(points.size());

		int pointIndex = 0;
		// Go through all points
		for (PointSet::iterator toPoint = points.begin(); toPoint != points.end(); toPoint++, pointIndex++)
		{	
			// Add a new entry in the distanceToPoint vector with the point and the distance
			distanceToPoint[*fromPoint][pointIndex] = std::make_pair((*toPoint), (*fromPoint)->valPos.getDistanceBetweenValuePositions((*toPoint)->valPos, points.getMaxPositionDistance(), points.getMaxValueDistance()));
		}
		// Sort the distanceToPoint vector depending on the distance value
		std::sort(distanceToPoint[*fromPoint].begin(), distanceToPoint[*fromPoint].end(), pairCompare);
	}
}

void ENearestClustering::addKNearestPointsToCluster(PointSet& points, Cluster& cluster, Point &pointToAdd, float nearestPointDistance)
{	
	// Go through all distanceToPoint entries while the distance between the pointToAdd and the point in the current distanceToPoint entry is less than nearestPointDistance
	for (int i = 1; i < distanceToPoint[&pointToAdd].size() && distanceToPoint[&pointToAdd][i].second <= nearestPointDistance; i++)
	{
		// If this point has no cluster yet
		if (distanceToPoint[&pointToAdd][i].first->cluster == NULL)
		{		
			// Set the cluster this point to the given cluster
			distanceToPoint[&pointToAdd][i].first->cluster = &cluster;
			// Add this point to the cluster
			cluster.points.push_back(distanceToPoint[&pointToAdd][i].first);	
		}
	}
}

float ENearestClustering::getBiggestDistance(PointSet& points)
{
	float biggestDistance = 0;
	// Go through all points
	for (PointSet::iterator point = points.begin(); point != points.end(); point++)
		biggestDistance = std::max(biggestDistance, distanceToPoint[*point].back().second);

	return biggestDistance;
}