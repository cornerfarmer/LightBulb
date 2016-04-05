#pragma once

#ifndef _ABSTRACTTRAININGPLANIO_H_
#define _ABSTRACTTRAININGPLANIO_H_

// Includes
#include "IO/NeuralNetworkIO.hpp"
#include "TrainingPlans/AbstractTrainingPlan.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void save(Archive& archive, AbstractTrainingPlan const& trainingPlan)
{
	std::unique_ptr<AbstractNeuralNetwork> neuralNetwork(trainingPlan.network);
	archive(cereal::make_nvp("neuralNetwork", neuralNetwork));
	neuralNetwork.release();
	archive(cereal::make_nvp("state", trainingPlan.state));
}

template <class Archive>
void load(Archive& archive, AbstractTrainingPlan& trainingPlan)
{
	std::unique_ptr<AbstractNeuralNetwork> neuralNetwork;
	archive(cereal::make_nvp("neuralNetwork", neuralNetwork));
	trainingPlan.network = neuralNetwork.release();
	archive(cereal::make_nvp("state", trainingPlan.state));
}

#endif