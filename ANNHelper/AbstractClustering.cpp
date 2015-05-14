#include "AbstractClustering.hpp"
#include "ValuePosition.hpp"
#include "Cluster.hpp"
#include "Point.hpp"

// Sets the minimum cluster width
const float AbstractClustering::minClusterWidth = 0.05f;

float AbstractClustering::getDistanceBetweenValuePositions(ValuePosition &valPos1, ValuePosition &valPos2)
{
	// Returns the distance between the positions of the two given points and also consider value differences
	// TODO: Improve value distance calculation
	return getDistanceBetweenPositions(valPos1.position, valPos2.position) * (1 + getDistanceBetweenPositions(valPos1.value, valPos2.value));
}

float AbstractClustering::getDistanceBetweenPositions(std::vector<float> &pos1, std::vector<float> &pos2)
{
	// Calculate the euclidean distance 
	float distance = 0;
	for (int p = 0; p < pos1.size(); p++)
		distance += pow(pos1[p] - pos2[p], 2);
	distance = sqrt(distance);
	return distance;
}

void AbstractClustering::calculateAllClusterWidths(std::list<Cluster> &clusters)
{
	// Go through all clusters
	for (std::list<Cluster>::iterator cluster = clusters.begin(); cluster != clusters.end(); cluster++)
	{
		// Set the radius to the minClusterWidth, so it will always be greater than 0
		(*cluster).radius = minClusterWidth;
		// Set the radius to the maximum distance between point and center of the cluster
		for (std::list<Point*>::iterator point = (*cluster).points.begin(); point != (*cluster).points.end(); point++)
			(*cluster).radius = std::max((*cluster).radius, getDistanceBetweenPositions((*point)->valPos.position, (*cluster).center.position));
	}
}

bool AbstractClustering::calculateClusterCentersFromMedians(std::list<Cluster> &clusters, bool withValue)
{
	bool somethingHasChanged = false;
	std::vector<std::vector<float>> clusterPositionMedian(clusters.size(), std::vector<float>(clusters.front().points.front()->valPos.position.size()));
	std::vector<std::vector<float>> clusterValueMedian(clusters.size(), std::vector<float>(clusters.front().points.front()->valPos.value.size()));

	int clusterIndex = 0;
	for (std::list<Cluster>::iterator cluster = clusters.begin(); cluster != clusters.end(); cluster++, clusterIndex++)
	{
		// Go through every point
		for (std::list<Point*>::iterator point = (*cluster).points.begin(); point != (*cluster).points.end(); point++)
		{				
			// Add the position of the point to the median of the choosen cluster
			for (int i = 0; i < (*point)->valPos.position.size(); i++)
			{
				clusterPositionMedian[clusterIndex][i] += (*point)->valPos.position[i];				
			}
			if (withValue)
			{
				// Add the position of the point to the median of the choosen cluster
				for (int i = 0; i < (*point)->valPos.value.size(); i++)
				{
					clusterValueMedian[clusterIndex][i] += (*point)->valPos.value[i];	
				}
			}
		}	
	}

	// Calculate new cluster positions from their medians
	// Go through all clusters
	clusterIndex = 0;
	for (std::list<Cluster>::iterator cluster = clusters.begin(); cluster != clusters.end(); cluster++, clusterIndex++)
	{
		if ((*cluster).points.size() != 0)
		{
			// Go through all dimensions of the position vector
			for (int i = 0; i < clusterPositionMedian[clusterIndex].size(); i++)
			{
				// Divide the sum of all points from this cluster by the point count, so now we have the median of the cluster
				clusterPositionMedian[clusterIndex][i] /= (*cluster).points.size();	
				if (clusterPositionMedian[clusterIndex][i] != (*cluster).center.position[i])
				{
					somethingHasChanged = true;
					(*cluster).center.position[i] = clusterPositionMedian[clusterIndex][i];
				}
			}
			if (withValue)
			{
				// Go through all dimensions of the position vector
				for (int i = 0; i < clusterValueMedian[clusterIndex].size(); i++)
				{
					// Divide the sum of all points from this cluster by the point count, so now we have the median of the cluster
					clusterValueMedian[clusterIndex][i] /= (*cluster).points.size();	
					if (clusterValueMedian[clusterIndex][i] != (*cluster).center.value[i])
					{
						somethingHasChanged = true;
						(*cluster).center.value[i] = clusterValueMedian[clusterIndex][i];
					}
				}
			}
		}
	}	

	return somethingHasChanged;
}