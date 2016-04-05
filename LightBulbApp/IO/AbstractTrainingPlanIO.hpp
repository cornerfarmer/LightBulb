#pragma once

#ifndef _ABSTRACTTRAININGPLANIO_H_
#define _ABSTRACTTRAININGPLANIO_H_

// Includes
#include "IO/NeuralNetworkIO.hpp"
#include "TrainingPlans/AbstractTrainingPlan.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <IO/IOStorage.hpp>

extern bool onlyUseNeuralNetworkIndex;

template <class Archive>
void save(Archive& archive, AbstractTrainingPlan const& trainingPlan)
{
	if (!onlyUseNeuralNetworkIndex)
	{
		std::unique_ptr<AbstractNeuralNetwork> neuralNetwork(trainingPlan.network);
		archive(cereal::make_nvp("neuralNetwork", neuralNetwork));
		neuralNetwork.release();
	}
	else
	{
		auto networks = IOStorage<std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::pop();
		int neuralNetworkIndex = 0;
		for (auto network = networks->begin(); network != networks->end(); network++, neuralNetworkIndex++)
		{
			if (network->get() == trainingPlan.network)
				break;
		}
		archive(cereal::make_nvp("neuralNetworkIndex", neuralNetworkIndex));
	}
	archive(cereal::make_nvp("state", trainingPlan.state));
}

template <class Archive>
void load(Archive& archive, AbstractTrainingPlan& trainingPlan)
{
	if (!onlyUseNeuralNetworkIndex)
	{
		std::unique_ptr<AbstractNeuralNetwork> neuralNetwork;
		archive(cereal::make_nvp("neuralNetwork", neuralNetwork));
		trainingPlan.network = neuralNetwork.release();
	}
	else
	{
		auto networks = IOStorage<std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::pop();
		int neuralNetworkIndex;
		archive(cereal::make_nvp("neuralNetworkIndex", neuralNetworkIndex));
		trainingPlan.network = (*networks)[neuralNetworkIndex].get();
	}
	archive(cereal::make_nvp("state", trainingPlan.state));
}

#endif