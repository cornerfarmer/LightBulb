#pragma once

#ifndef _RBFTHRESHOLD_H_
#define _RBFTHRESHOLD_H_

// Library Includes
#include <vector>

// Includes
#include "Neuron\AbstractThreshold.hpp"

// A StandardThreshold just consists of one double value
class RBFThreshold : public AbstractThreshold
{
private:
	// The center of the RBF-Neuron
	std::vector<double> centerVector;
	// The width of the RBF-Neuron
	double width;
public:
	RBFThreshold(std::vector<double> &centerVector_, double width_);
	void setCenterVector(std::vector<double> &newCenterVector);
	std::vector<double>* getCenterVector();
	double getWidth();
	void setWidth(double newWidth);
	// Inherited:
	AbstractThreshold* getCopy();
};

#endif