#pragma once

#ifndef _VALUEPOSITION_H_
#define _VALUEPOSITION_H_

// Library includes
#include <vector>

// This class contains all stuff needed to describe a Point 
struct ValuePosition
{
	// Position of the point
	std::vector<float> position;
	// Value of the point
	std::vector<float> value;	

	ValuePosition(std::vector<float> &position_, std::vector<float> &value_)
	{
		position = position_;
		value = value_;
	}

	ValuePosition()
	{
	}

	// Calculates the (value and position) distance between two valuePositions
	float getDistanceBetweenValuePositions(ValuePosition &otherValuePosition)
	{
		// Returns the distance between the positions of the own valuePosition and the given one and also consider value differences
		// TODO: Improve value distance calculation
		return getPositionDistance(otherValuePosition) * (1 + getValueDistance(otherValuePosition));
	}
	
	// Calculates the distance between two positions
	float getPositionDistance(ValuePosition &otherValuePosition)
	{
		// Calculate the euclidean distance 
		float distance = 0;
		for (int p = 0; p < position.size(); p++)
			distance += pow(position[p] - otherValuePosition.position[p], 2);
		distance = sqrt(distance);
		return distance;
	}

	// Calculates the distance between two values
	float getValueDistance(ValuePosition &otherValuePosition)
	{
		// Calculate the euclidean distance 
		float distance = 0;
		for (int p = 0; p < value.size(); p++)
			distance += pow(value[p] - otherValuePosition.value[p], 2);
		distance = sqrt(distance);
		return distance;
	}
};

#endif