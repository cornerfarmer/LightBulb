#pragma once

#ifndef _VALUEPOSITION_H_
#define _VALUEPOSITION_H_

// Library includes
#include <vector>

// This struct contains all stuff needed to describe a ValuePosition 
struct ValuePosition
{
	// Position of the point
	std::vector<float> position;
	// Value of the point
	std::vector<float> value;	
	// Sets the relation between the position and the value distance 
	static const float valuePositionRelation;

	ValuePosition(std::vector<float> &position_, std::vector<float> &value_);
	ValuePosition();
	// Calculates the (value and position) distance between two valuePositions
	float getDistanceBetweenValuePositions(ValuePosition &otherValuePosition, float maxPositionDistance, float maxValueDistance);
	// Calculates the distance between two positions
	float getPositionDistance(ValuePosition &otherValuePosition);
	// Calculates the distance between two values
	float getValueDistance(ValuePosition &otherValuePosition);

};

#endif