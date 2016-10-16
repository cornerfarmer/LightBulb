#pragma once

#ifndef _EvolutionAnalyzerCONTROLLER_H_
#define _EvolutionAnalyzerCONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "EvolutionAnalyzerWindow.hpp"
#include "AbstractSubApp.hpp"
#include <TrainingPlans/AbstractEvolutionTrainingPlan.hpp>
#include <Learning/Evolution/AbstractEvolutionObject.hpp>

namespace LightBulb
{
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
		std::vector<std::pair<EvolutionSource, double>> currentState;
	protected:
		void prepareClose() override;
	public:
		EvolutionAnalyzerController(AbstractMainApp* mainApp, TrainingPlanRepository* trainingPlanRepository, AbstractWindow* parent = nullptr);
		void trainingPlansChanged(TrainingPlanRepository* trainingPlanRepository);
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans() const;
		EvolutionAnalyzerWindow* getWindow();
		static const std::string& getLabel();
		void selectTrainingPlan(int trainingPlanIndex);
		void evolutionStepCompleted(EvolutionLearningRule* evolutionLearningRule);
		const std::vector<std::pair<EvolutionSource, double>>* getCurrentState() const;
	};
}

#endif
