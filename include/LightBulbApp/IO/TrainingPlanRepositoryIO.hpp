#pragma once

#ifndef _TRAININGPLANREPOSITORYIO_H_
#define _TRAININGPLANREPOSITORYIO_H_

// Includes
#include "LightBulbApp/Repositories/TrainingPlanRepository.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a TrainingPlanRepository.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlanRepository The TrainingPlanRepository to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, TrainingPlanRepository& trainingPlanRepository);
}

#endif