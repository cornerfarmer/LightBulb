#pragma once

#ifndef _ABSTRACTSINGLENNTRAININGPLANIO_H_
#define _ABSTRACTSINGLENNTRAININGPLANIO_H_

// Includes
#include "TrainingPlans/AbstractSingleNNTrainingPlan.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <IO/IOStorage.hpp>

extern bool onlyUseNeuralNetworkIndex;

template <class Archive>
void save(Archive& archive, AbstractSingleNNTrainingPlan const& trainingPlan)
{
	if (!onlyUseNeuralNetworkIndex)
	{
		std::unique_ptr<AbstractNeuralNetwork> neuralNetwork(trainingPlan.network);
		archive(cereal::make_nvp("neuralNetwork", neuralNetwork));
		neuralNetwork.release();
	}
	else
	{
		auto networks = IOStorage<std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::get();
		int neuralNetworkIndex = 0;
		for (auto network = networks->begin(); network != networks->end(); network++, neuralNetworkIndex++)
		{
			if (network->get() == trainingPlan.network)
				break;
		}
		archive(cereal::make_nvp("neuralNetworkIndex", neuralNetworkIndex));
	}
	archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
}

template <class Archive>
void load(Archive& archive, AbstractSingleNNTrainingPlan& trainingPlan)
{
	if (!onlyUseNeuralNetworkIndex)
	{
		std::unique_ptr<AbstractNeuralNetwork> neuralNetwork;
		archive(cereal::make_nvp("neuralNetwork", neuralNetwork));
		trainingPlan.network = neuralNetwork.release();
	}
	else
	{
		auto networks = IOStorage<std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::get();
		int neuralNetworkIndex;
		archive(cereal::make_nvp("neuralNetworkIndex", neuralNetworkIndex));
		trainingPlan.network = (*networks)[neuralNetworkIndex].get();
	}
	archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(AbstractSingleNNTrainingPlan);

#endif