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
};

#endif