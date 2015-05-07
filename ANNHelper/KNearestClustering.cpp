#include "KNearestClustering.hpp"
#include "Cluster.hpp"
#include <algorithm>
#include <map>
#include "Point.hpp"
#include "KMeansClustering.hpp"


std::unique_ptr<std::list<Cluster>> KNearestClustering::doClustering(std::list<Point*> &points, int clusterCount, int dimensionCount) 
{
	int intervalBegin = 0;
	int intervalEnd = points.size() - 1;

	std::unique_ptr<std::list<Cluster>> clusters;
	bool useCache = false;
	flushCache(points.size());
	do
	{
		clusters.reset(doClustering(points, (intervalEnd - intervalBegin) / 2 + intervalBegin, dimensionCount, useCache));
		if (clusters->size() == clusterCount)
			break;
		else 
		{
			if (clusters->size() > clusterCount)
			{
				if (intervalEnd - intervalBegin == 1)
				{
					intervalBegin++;
					intervalEnd++;
				}
				else
					intervalBegin = (intervalEnd - intervalBegin) / 2 + intervalBegin;
			}
			else
			{
				intervalEnd = (intervalEnd - intervalBegin) / 2 + intervalBegin;
			}
			
		}
		useCache = true;
	} while(intervalBegin != intervalEnd);

	

	int neededClustersLeft = clusterCount - clusters->size();

	if (neededClustersLeft > 0)
	{
		KMeansClustering kMeansclustering;		
		int originalClusterCount = clusters->size();
		for (int clusterIndex = 0; clusterIndex < originalClusterCount; clusterIndex++)
		{		
			 
			int subClusterCount = 1;
			if (clusterIndex == originalClusterCount - 1)
				subClusterCount += clusterCount - clusters->size();
			else
				subClusterCount += neededClustersLeft * clusters->front().points.size() / points.size();

			std::unique_ptr<std::list<Cluster>> newSubClusters = kMeansclustering.doClustering(clusters->front().points, subClusterCount, dimensionCount);

			clusters->pop_front();
			clusters->insert(clusters->end(), newSubClusters->begin(), newSubClusters->end());
		}
	}
	calculateAllClusterWidths(*clusters.get());
	return clusters;
}

std::list<Cluster>* KNearestClustering::doClustering(std::list<Point*> &points, int nearestPointsCount, int dimensionCount, bool useCache)
{
	// Create a new cluster vector
	std::list<Cluster>* clusters = new std::list<Cluster>();
	// Go through every point

	for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)		
		(*point)->cluster = NULL;

	// Add every point to its nearest cluster
	// Go through every point
	for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
	{		
		if ((*point)->cluster == NULL)
		{
			Cluster newCluster;
			newCluster.position.resize(dimensionCount);
			newCluster.width = 0.5f;
			clusters->push_back(newCluster);
			addKNearestPointsToCluster(points, clusters->back(), *(*point), nearestPointsCount, useCache);
		}		
	}

	// Add every point to its nearest cluster
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

	return clusters;
}

void KNearestClustering::addKNearestPointsToCluster(std::list<Point*>& points, Cluster& cluster, Point &pointToAdd, int nearestPointsCount, bool useCache)
{
	pointToAdd.cluster = &cluster;
	cluster.points.push_back(&pointToAdd);

	
	if (!useCache)
	{
		distanceToPointCache[&pointToAdd] = std::vector<std::pair<Point*, float>>();
		for (std::list<Point*>::iterator point = points.begin(); point != points.end(); point++)
		{	
			distanceToPointCache[&pointToAdd].push_back(std::make_pair((*point), getDistanceBetweenPoints(pointToAdd, *(*point))));
		}
		std::sort(distanceToPointCache[&pointToAdd].begin(), distanceToPointCache[&pointToAdd].end(), pairCompare);
	}

	for (int p = 1; p < nearestPointsCount + 1; p++)
	{
		if (distanceToPointCache[&pointToAdd][p].first->cluster == NULL)
			addKNearestPointsToCluster(points, cluster, *distanceToPointCache[&pointToAdd][p].first, nearestPointsCount, useCache);
	}
}

void KNearestClustering::flushCache(int pointCount)
{
	distanceToPointCache.clear();
}

bool KNearestClustering::pairCompare(const std::pair<Point*, float>& a ,const std::pair<Point*, float>& b)
{
	return a.second < b.second;
}