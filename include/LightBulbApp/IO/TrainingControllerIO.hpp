#pragma once

#ifndef _TRAININGCONTROLLERIO_H_
#define _TRAININGCONTROLLERIO_H_

// Includes
#include "LightBulbApp/Windows/TrainingController.hpp"
#include "LightBulbApp/Repositories/NeuralNetworkRepository.hpp"
#include "LightBulbApp/Repositories/TrainingPlanRepository.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a TrainingController.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingController The TrainingController to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, TrainingController& trainingController)
	{
		serialize(archive, *trainingController.neuralNetworkRepository);

		IOStorage<const std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::push(&trainingController.neuralNetworkRepository->getNeuralNetworks());
		serialize(archive, *trainingController.trainingPlanRepository);
		IOStorage<const std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::clear();
	}
}


#endif
