#pragma once

#ifndef _LEARNINGSTATEFACTORY_H_
#define _LEARNINGSTATEFACTORY_H_

// Includes
#include "AbstractSubAppFactory.hpp"

namespace LightBulb
{
	// Forward declarations
	class TrainingPlanRepository;
	/**
	* \brief A factory for the learning state sub app.
	*/
	class LearningStateFactory : public AbstractSubAppFactory
	{
	protected:
		/**
		* \brief The training plan repository to use.
		*/
		TrainingPlanRepository* trainingPlanRepository;
	public:
		/**
		* \brief Creates the factory.
		* \param trainingPlanRepository_ The training plan repository to use.
		*/
		LearningStateFactory(TrainingPlanRepository& trainingPlanRepository_);
		// Inherited:
		AbstractSubApp* createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const override;
		std::string getLabel() const override;
	};
}

#endif
