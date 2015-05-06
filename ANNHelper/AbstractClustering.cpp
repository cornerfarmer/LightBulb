#include "AbstractClustering.hpp"
#include "Point.hpp"

float AbstractClustering::getDistanceBetweenPoints(Point &point1, Point &point2)
{
	return getDistanceBetweenPositions(point1.position, point2.position) * (1 + getDistanceBetweenPositions(point1.value, point2.value));
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
