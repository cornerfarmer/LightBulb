#include "ValuePosition.hpp"

// Sets the relation between the position and the value distance 
const float ValuePosition::valuePositionRelation = 0.2;

ValuePosition::ValuePosition(std::vector<float> &position_, std::vector<float> &value_)
{
	position = position_;
	value = value_;
}

ValuePosition::ValuePosition()
{
}

// Calculates the (value and position) distance between two valuePositions
float ValuePosition::getDistanceBetweenValuePositions(ValuePosition &otherValuePosition, float maxPositionDistance, float maxValueDistance)
{
	// If a max distance is zero, return also zero
	if (maxPositionDistance == 0 || maxValueDistance == 0)
		return 0;
	else
	{
		// Returns the distance between the positions of the own valuePosition and the given one and also consider value differences
		return getPositionDistance(otherValuePosition) / maxPositionDistance + getValueDistance(otherValuePosition) / maxValueDistance * valuePositionRelation;
	}
}
	
// Calculates the distance between two positions
float ValuePosition::getPositionDistance(ValuePosition &otherValuePosition)
{
	// Calculate the euclidean distance 
	float distance = 0;
	for (int p = 0; p < position.size(); p++)
		distance += pow(position[p] - otherValuePosition.position[p], 2);
	distance = sqrt(distance);
	return distance;
}

// Calculates the distance between two values
float ValuePosition::getValueDistance(ValuePosition &otherValuePosition)
{
	// Calculate the euclidean distance 
	float distance = 0;
	for (int p = 0; p < value.size(); p++)
		distance += pow(value[p] - otherValuePosition.value[p], 2);
	distance = sqrt(distance);
	return distance;
}
