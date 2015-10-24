#pragma once

#ifndef _MUTATIONALGORITHM_H_
#define _MUTATIONALGORITHM_H_

// Library Includes
#include <random>

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"

// Forward declarations
class AbstractEvolutionObject;

class MutationAlgorithm : public AbstractMutationAlgorithm
{
private:
	std::default_random_engine generator;
	std::normal_distribution<double> distribution;
	double mutationStrengthChangeSpeed;
	double mutationStrengthMin;
	double mutationStrengthMax;
public:
	MutationAlgorithm(double mutationStrengthChangeSpeed_);
	void execute(AbstractEvolutionObject* object1);
	void setMutationStrengthChangeSpeed(double mutationStrengthChangeSpeed_);
};

#endif
