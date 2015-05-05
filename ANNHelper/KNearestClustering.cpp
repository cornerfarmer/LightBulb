#include "KNearestClustering.hpp"
#include "Cluster.hpp"
#include <algorithm>
#include <map>

std::unique_ptr<std::vector<Cluster>> KNearestClustering::doClustering(std::vector<std::vector<float>>* points, int nearestPointsCount, int dimensionCount)
{
	// Create a new cluster vector
	std::unique_ptr<std::vector<Cluster>> clusters(new std::vector<Cluster>());

	// This vector contains informations about which point referrs to which cluster
	std::vector<int> clusterFromPoint(points->size(), -1);

	// Add every point to its nearest cluster
	// Go through every point
	for (int p = 0; p < points->size(); p++)
	{		
		if (clusterFromPoint[p] == -1)
		{
			Cluster newCluster;
			newCluster.position.resize(dimensionCount);
			newCluster.width = 0.5f;
			newCluster.pointCount = 0;
			clusters->push_back(newCluster);
			addKNearestPointsToCluster(*points, clusterFromPoint, *clusters, p, clusters->size() - 1, nearestPointsCount);
		}		
	}

	// Add every point to its nearest cluster
	// Go through every point
	for (int p = 0; p < points->size(); p++)
	{			
		// Add the position of the point to the median of the choosen cluster
		for (int i = 0; i < dimensionCount; i++)
			(*clusters)[clusterFromPoint[p]].position[i] += (*points)[p][i];
	}	

	// Calculate new cluster positions from their medians
	// Go through all clusters
	for (int c = 0; c < clusters->size(); c++)
	{
		// Go through all dimensions of the position vector
		for (int i = 0; i < dimensionCount; i++)
		{
			// Divide the sum of all points from this cluster by the point count, so now we have the median of the cluster
			(*clusters)[c].position[i] /= (*clusters)[c].pointCount;	
		}
	}	

	return clusters;
}

void KNearestClustering::addKNearestPointsToCluster(std::vector<std::vector<float>>& points, std::vector<int>& clusterFromPoint, std::vector<Cluster>& clusters, int pointIndex, int clusterIndex, int nearestPointsCount)
{
	clusterFromPoint[pointIndex] = clusterIndex;
	clusters[clusterFromPoint[pointIndex]].pointCount++;

	std::vector<std::pair<int, float>> distanceToPoint;
	for (int p = 0; p < points.size(); p++)
	{
		distanceToPoint.push_back(std::pair<int, float>(p, getDistanceBetweenPoints(points[pointIndex], points[p])));
	}

	std::sort(distanceToPoint.begin(), distanceToPoint.end(), pairCompare);

	for (int p = 1; p < nearestPointsCount + 1; p++)
	{
		if (clusterFromPoint[distanceToPoint[p].first] == -1)
			addKNearestPointsToCluster(points, clusterFromPoint, clusters, distanceToPoint[p].first, clusterIndex, nearestPointsCount);
	}
}

bool KNearestClustering::pairCompare(const std::pair<int, float>& a ,const std::pair<int, float>& b)
{
	return a.second < b.second;
}