#pragma once

#ifndef _ABSTRACTSINGLENNTRAININGPLANIO_H_
#define _ABSTRACTSINGLENNTRAININGPLANIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/AbstractSupervisedTrainingPlan.hpp"

namespace LightBulb
{
	/**
	 * \brief Set true if the training plan should only serialize the index of the network in the network respository.
	 */
	extern bool onlyUseNeuralNetworkIndex;

	/**
	* \brief Saves an AbstractSupervisedTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractSupervisedTrainingPlan to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, AbstractSupervisedTrainingPlan const& trainingPlan);

	/**
	* \brief Loads an AbstractSupervisedTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractSupervisedTrainingPlan to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractSupervisedTrainingPlan& trainingPlan);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(AbstractSupervisedTrainingPlan)

#endif