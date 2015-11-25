#pragma once

#ifndef _VALUEPOSITION_H_
#define _VALUEPOSITION_H_

// Library includes
#include <vector>

// This struct contains all stuff needed to describe a ValuePosition 
struct ValuePosition
{
	// Position of the point
	std::vector<double> position;
	// Value of the point
	std::vector<double> value;	
	// Sets the relation between the position and the value distance 
	static const double valuePositionRelation;

	ValuePosition(std::vector<double> &position_, std::vector<double> &value_);
	ValuePosition();
	// Calculates the (value and position) distance between two valuePositions
	double getDistanceBetweenValuePositions(ValuePosition &otherValuePosition, double maxPositionDistance, double maxValueDistance);
	// Calculates the distance between two positions
	double getPositionDistance(ValuePosition &otherValuePosition);
	// Calculates the distance between two values
	double getValueDistance(ValuePosition &otherValuePosition);

};

#endif