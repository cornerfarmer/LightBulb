#pragma once

#ifndef _ABSTRACTTRAININGPLANIO_H_
#define _ABSTRACTTRAININGPLANIO_H_

// Includes
#include "IO/NeuralNetworkIO.hpp"
#include "TrainingPlans/AbstractTrainingPlan.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, AbstractTrainingPlan& trainingPlan)
{
	std::unique_ptr<AbstractNeuralNetwork> neuralNetwork(trainingPlan.network);
	archive(CEREAL_NVP(neuralNetwork));
	trainingPlan.network = neuralNetwork.release();
}

#endif