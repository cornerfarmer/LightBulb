#pragma once

#ifndef _KNEARESTRBFNEURONPLACER_H_
#define _KNEARESTRBFNEURONPLACER_H_

// Library includes

// Includes
#include "AbstractRBFNeuronPlacer.hpp"

// Forward declarations
class RBFNetwork;
class Teacher;

// This class contains all stuff needed to describe a RBFNeuronPlacer 
class KNearestRBFNeuronPlacer : public AbstractRBFNeuronPlacer
{
protected:
public:
	void doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher);
	AbstractRBFNeuronPlacer* getCopy();
};

#endif