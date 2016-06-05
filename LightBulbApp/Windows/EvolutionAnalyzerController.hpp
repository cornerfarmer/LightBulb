#pragma once

#ifndef _EvolutionAnalyzerCONTROLLER_H_
#define _EvolutionAnalyzerCONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "EvolutionAnalyzerWindow.hpp"
#include "AbstractSubApp.hpp"
#include <TrainingPlans/AbstractEvolutionTrainingPlan.hpp>

// Forward declarations
class TrainingWindow;
class TrainingPlanRepository;
class EvolutionLearningRule;

class EvolutionAnalyzerController : public AbstractSubApp
{
private:
	std::unique_ptr<EvolutionAnalyzerWindow> window;
	TrainingPlanRepository* trainingPlanRepository;
	AbstractEvolutionTrainingPlan* selectedTrainingPlan;
	Highscore currentHighscore;
protected:
	void prepareClose();
public:
	EvolutionAnalyzerController(AbstractMainApp* mainApp, TrainingPlanRepository* trainingPlanRepository, AbstractWindow* parent = NULL);
	void trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository);
	std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans();
	EvolutionAnalyzerWindow* getWindow();
	static std::string getLabel();
	void selectTrainingPlan(int trainingPlanIndex);
	void evolutionStepCompleted(EvolutionLearningRule* evolutionLearningRule);
	Highscore* getCurrentHighscore();
};

#endif
