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
	/**
	 * \brief A sub app which describes the source of all current evolution objects.
	 * \details Lists all evolution objects of a evolution learning rule, shows their source and their score. (Mutation, Recombination, Resuse, Create)
	 */
	class EvolutionAnalyzerController : public AbstractSubApp
	{
	private:
		/**
		 * \brief The corresponding windiw.
		 */
		EvolutionAnalyzerWindow* window;
		/**
		 * \brief The training plan repository.
		 * \details Used for listing all current training plans.
		 */
		TrainingPlanRepository* trainingPlanRepository;
		/**
		 * \brief The current selected training plan.
		 */
		AbstractEvolutionTrainingPlan* selectedTrainingPlan;
		/**
		 * \brief The current state.
		 * \details A map: source => score.
		 */
		std::vector<std::pair<EvolutionSource, double>> currentState;
	protected:
		// Inherited:
		void prepareClose() override;
	public:
		/**
		 * \brief Creates the EvolutionAnalyzerController.
		 * \param mainApp The main app which should manage the sub app.
		 * \param trainingPlanRepository The training plan repository.
		 * \param parent The parent window.
		 */
		EvolutionAnalyzerController(AbstractMainApp& mainApp, TrainingPlanRepository& trainingPlanRepository, AbstractWindow& parent);
		/**
		 * \brief Is called when the training plan repository has changed.
		 * \param trainingPlanRepository The training plan repository.
		 */
		void trainingPlansChanged(TrainingPlanRepository& trainingPlanRepository);
		/**
		 * \brief Returns the current training plans.
		 * \return The current training plans.
		 */
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>& getTrainingPlans() const;
		/**
		 * \brief Returns the corresponding window.
		 * \return The window.
		 */
		EvolutionAnalyzerWindow& getWindow();
		/**
		 * \brief Returns the label of the sub app.
		 * \return The label.
		 */
		static std::string getLabel();
		/**
		 * \brief Selects the training plan with the given index.
		 * \param trainingPlanIndex The index of the training plan to select.
		 */
		void selectTrainingPlan(int trainingPlanIndex);
		/**
		 * \brief Is called after every evolution step.
		 * \param evolutionLearningRule The evolution learning rule.
		 */
		void evolutionStepCompleted(EvolutionLearningRule& evolutionLearningRule);
		/**
		 * \brief Returns the current state.
		 * \return A map with: evolution source => score.
		 */
		const std::vector<std::pair<EvolutionSource, double>>& getCurrentState() const;
	};
}

#endif
