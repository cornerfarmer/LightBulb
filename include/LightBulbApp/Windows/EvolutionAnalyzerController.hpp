#pragma once

#ifndef _EvolutionAnalyzerCONTROLLER_H_
#define _EvolutionAnalyzerCONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "AbstractSubApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class TrainingWindow;
	class TrainingPlanRepository;
	class EvolutionLearningRule;
	class EvolutionAnalyzerWindow;
	class AbstractEvolutionTrainingPlan;
	enum EvolutionSource;
	class AbstractWindow;
	class AbstractTrainingPlan;
	/**
	 * \brief A sub app which describes the source of all current individuals.
	 * \details Lists all individuals of a evolution learning rule, shows their source and their fitness. (Mutation, Recombination, Resuse, Create)
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
		 * \details A map: source => fitness.
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
		 * \return A map with: evolution source => fitness.
		 */
		const std::vector<std::pair<EvolutionSource, double>>& getCurrentState() const;
	};
}

#endif
