#pragma once

#ifndef _BACKPROPAGATION_H_
#define _BACKPROPAGATION_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractGradientCalculation.hpp"

// Forward declarations


// The BackpropagationLearningRule can  be used to train MultiPerceptronNetworks
class Backpropagation : public AbstractGradientCalculation
{
	template <class Archive>
	friend void serialize(Archive& archive, Backpropagation& backpropagation);
	friend struct cereal::LoadAndConstruct<Backpropagation>;
private:	
	// This vector should hold all delta values
	Eigen::VectorXd lastDeltaVectorOutputLayer;
	double flatSpotEliminationFac;
public:
	Backpropagation(double flatSpotEliminationFac_ = 0);
	void calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap, std::vector<Eigen::MatrixXd>& gradient) override;
};

#include "IO/BackpropagationIO.hpp"

#endif

