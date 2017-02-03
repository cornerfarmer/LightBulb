#pragma once

#ifndef _EVOLUTIONANALYZERFACTORY_H_
#define _EVOLUTIONANALYZERFACTORY_H_

// Includes
#include "AbstractSubAppFactory.hpp"

namespace LightBulb
{
	// Forward declarations
	class TrainingPlanRepository;
	/**
	 * \brief A factory for the evolution analyzer sub app.
	 */
	class EvolutionAnalyzerFactory : public AbstractSubAppFactory
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
		EvolutionAnalyzerFactory(TrainingPlanRepository& trainingPlanRepository_);
		// Inherited:
		AbstractSubApp* createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const override;
		std::string getLabel() const override;
	};
}

#endif
