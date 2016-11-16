#pragma once

#ifndef _ABSTRACTSINGLENNTRAININGPLAN_H_
#define _ABSTRACTSINGLENNTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"

// Library includes

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	struct AbstractSupervisedLearningRuleOptions;
	/**
	 * \brief Describes a training plan which uses classic supervised learning.
	 */
	class AbstractSupervisedTrainingPlan : public AbstractLearningRuleTrainingPlan
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractSupervisedTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractSupervisedTrainingPlan& trainingPlan);
	protected:
		/**
		 * \brief The network which is used.
		 * \note The network is managed by the network repository.
		 */
		AbstractNeuralNetwork* network;
		/**
		 * \brief Creates the network to train.
		 * \return The created network.
		 */
		virtual AbstractNeuralNetwork* createNeuralNetwork() = 0;
		/**
		* \brief Fills all learning rule options which are the same for all supervised learning rule training plans.
		* \param options The options to fill.
		*/
		void fillDefaultLearningRuleOptions(AbstractSupervisedLearningRuleOptions& options) const;
	public:
		/**
		 * \brief Creates the supervised training plan.
		 */
		AbstractSupervisedTrainingPlan();
		/**
		 * \brief Returns the trained neural network.
		 * \return The neural network.
		 */
		AbstractNeuralNetwork& getNeuralNetwork();
		// Inherited:
		void initializeStart() override;
	};
}

#include "IO/AbstractSingleNNTrainingPlanIO.hpp"

#endif
