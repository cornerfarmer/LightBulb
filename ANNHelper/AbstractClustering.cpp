#include "AbstractClustering.hpp"

float AbstractClustering::getDistanceBetweenPoints(std::vector<float> &point1, std::vector<float> &point2)
{
	// Calculate the euclidean distance 
	float distance = 0;
	for (int p = 0; p < point1.size(); p++)
		distance += pow(point1[p] - point2[p], 2);
	distance = sqrt(distance);
	return distance;
}