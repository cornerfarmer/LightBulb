#pragma once

#ifndef _EVOLUTIONANALYZERFACTORY_H_
#define _EVOLUTIONANALYZERFACTORY_H_

// Includes
#include "AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

// Forward declarations
class TrainingPlanRepository;

class EvolutionAnalyzerFactory : public AbstractSubAppFactory
{
protected:
	TrainingPlanRepository* trainingPlanRepository;
public:
	EvolutionAnalyzerFactory(TrainingPlanRepository* trainingPlanRepository_);
	AbstractSubApp* createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent) override;
	std::string getLabel() override;
};

#endif
