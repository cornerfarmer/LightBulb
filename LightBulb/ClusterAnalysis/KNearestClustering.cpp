#include "ClusterAnalysis\KNearestClustering.hpp"
#include "ClusterAnalysis\Cluster.hpp"
#include <algorithm>
#include "ClusterAnalysis\Point.hpp"
#include "ClusterAnalysis\PointSet.hpp"

void KNearestClustering::calculateCache(PointSet& points)
{
	// Create a map entry for every point in points
	for (PointSet::iterator point = points.begin(); point != points.end(); point++)
		nthNearestPointToPoint[*point] = std::vector<std::pair<Point*, int>>();

	// Go through a ll points
	for (PointSet::iterator fromPoint = points.begin(); fromPoint != points.end(); fromPoint++)
	{
		// Create a vector which will contain all distances from the current point to all other points
		std::vector<std::pair<Point*, double>> distanceToPoint(points.size());

		int pointIndex = 0;
		// Go through all points
		for (PointSet::iterator toPoint = points.begin(); toPoint != points.end(); toPoint++, pointIndex++)
		{	
			// Add a new entry in the distanceToPoint vector with the point and the distance
			distanceToPoint[pointIndex] = std::make_pair((*toPoint), (*fromPoint)->valPos.getDistanceBetweenValuePositions((*toPoint)->valPos, points.getMaxPositionDistance(), points.getMaxValueDistance()));
		}
		// Sort the distanceToPoint vector depending on the distance value
		std::sort(distanceToPoint.begin(), distanceToPoint.end(), pairCompare);

		// Go from the second nearest point through all points in the distanceToPoint vector in the new order (the first one will be the point itself ;) )
		for (int i = 1, nth = 0; i < distanceToPoint.size(); i++)
		{
			// If the distance has changed between the last element in the vector and the current one, increase the nth counter
			if (distanceToPoint[i].second != distanceToPoint[i - 1].second)
				nth++;
			// Add a new pair to list of nthNearestPointsfromPoint
			nthNearestPointToPoint[distanceToPoint[i].first].push_back(std::make_pair(*fromPoint, nth));			
		}
	}
}

void KNearestClustering::addKNearestPointsToCluster(PointSet& points, Cluster& cluster, Point &pointToAdd, double nearestPointsCount)
{	
	// Go through all nthNearestPointToPoint entries
	for (int i = 0; i < nthNearestPointToPoint[&pointToAdd].size(); i++)
	{
		// If the pointToAdd is in the n-th (nearestPointsCount) nearest points from the point in the nthNearestPointToPoint entry and this point has no cluster yet
		if (nthNearestPointToPoint[&pointToAdd][i].first->cluster == NULL && nthNearestPointToPoint[&pointToAdd][i].second <= nearestPointsCount)
		{		
			// Set the cluster this point to the given cluster
			nthNearestPointToPoint[&pointToAdd][i].first->cluster = &cluster;
			// Add this point to the cluster
			cluster.points.push_back(nthNearestPointToPoint[&pointToAdd][i].first);	
		}
	}
}
