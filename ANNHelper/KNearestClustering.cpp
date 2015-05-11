#include "KNearestClustering.hpp"
#include "Cluster.hpp"
#include <algorithm>
#include <map>
#include "Point.hpp"
#include "KMeansClustering.hpp"


std::unique_ptr<std::list<Cluster>> KNearestClustering::doClustering(std::list<Point*> &points, int nearestPointsCount, int dimensionCount) 
{	
	// Create a new cluster list
	std::unique_ptr<std::list<Cluster>> clusters(new std::list<Cluster>());

	// Go through every point and set the cluster to null
	for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)		
		(*point)->cluster = NULL;

	// Group every point with its k nearest points
	// Go through every point
	for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
	{		
		// If the point does not have already a cluster
		if ((*point)->cluster == NULL)
		{
			// Create a new Cluster for this point
			Cluster newCluster;
			// Set the position size to the given dimension
			newCluster.position.resize(dimensionCount);
			// Add the new cluster to the cluster list
			clusters->push_back(newCluster);

			// Set the cluster of the current point to the new cluster
			(*point)->cluster = &clusters->back();
			// Add the point to the cluster
			(*point)->cluster->points.push_back(*point);
			
			// Go through all points in this cluster and add all points, which have the pointInCluster in their k-nearest points list
			for (std::list<Point*>::iterator pointInCluster = (*point)->cluster->points.begin(); pointInCluster != (*point)->cluster->points.end(); pointInCluster++)
				addKNearestPointsToCluster(points, clusters->back(), *(*pointInCluster), nearestPointsCount);
		}		
	}
		
	// Go through every point
	for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
	{				
		// Add the position of the point to the median of the choosen cluster
		for (int i = 0; i < dimensionCount; i++)
			(*point)->cluster->position[i] += (*point)->position[i];
	}	

	// Calculate new cluster positions from their medians
	// Go through all clusters
	for (std::list<Cluster>::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++)
	{
		// Go through all dimensions of the position vector
		for (int i = 0; i < dimensionCount; i++)
		{
			// Divide the sum of all points from this cluster by the point count, so now we have the median of the cluster
			(*cluster).position[i] /= (*cluster).points.size();	
		}
	}	

	// Calculate the widths of all calculated clusters
	calculateAllClusterWidths(*clusters.get());
	return clusters;
}

void KNearestClustering::calculateCache(std::list<Point*>& points)
{
	// Create a map entry for every point in points
	for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
		nthNearestPointToPoint[*point] = std::vector<std::pair<Point*, int>>();

	// Go through a ll points
	for (std::list<Point*>::iterator fromPoint = points.begin(); fromPoint != points.end(); fromPoint++)
	{
		// Create a vector which will contain all distances from the current point to all other points
		std::vector<std::pair<Point*, float>> distanceToPoint(points.size());

		int pointIndex = 0;
		// Go through all points
		for (std::list<Point*>::iterator toPoint = points.begin(); toPoint != points.end(); toPoint++, pointIndex++)
		{	
			// Add a new entry in the distanceToPoint vector with the point and the distance
			distanceToPoint[pointIndex] = std::make_pair((*toPoint), getDistanceBetweenPoints(**fromPoint, **toPoint));
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

void KNearestClustering::addKNearestPointsToCluster(std::list<Point*>& points, Cluster& cluster, Point &pointToAdd, int nearestPointsCount)
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

bool KNearestClustering::pairCompare(const std::pair<Point*, float>& a ,const std::pair<Point*, float>& b)
{
	return a.second < b.second;
}