#include "AbstractNearestClustering.hpp"
#include "Cluster.hpp"
#include "Point.hpp"

std::unique_ptr<std::list<Cluster>> AbstractNearestClustering::doClustering(std::list<Point*> &points, float nearestPointsCount, int dimensionCount) 
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

bool AbstractNearestClustering::pairCompare(const std::pair<Point*, float>& a ,const std::pair<Point*, float>& b)
{
	return a.second < b.second;
}