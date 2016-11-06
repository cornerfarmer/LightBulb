#pragma once

#ifndef _LOGGERFACTORY_H_
#define _LOGGERFACTORY_H_

// Includes
#include "AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

namespace LightBulb
{
	// Forward declarations
	class TrainingPlanRepository;
	/**
	* \brief A factory for the logger sub app.
	*/
	class LoggerFactory : public AbstractSubAppFactory
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
		LoggerFactory(TrainingPlanRepository& trainingPlanRepository_);
		// Inherited:
		AbstractSubApp* createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const override;
		std::string getLabel() const override;
	};
}

#endif
