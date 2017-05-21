#pragma once

#ifndef _APP_H_
#define _APP_H_

// Includes
#include "Repositories/NeuralNetworkRepository.hpp"
#include "Repositories/TrainingPlanRepository.hpp"
#include "Windows/TrainingController.hpp"

// Library includes
#include <wx/wxprec.h>
#include <memory>

namespace LightBulb
{
	class AbstractTrainingPlan;
	class AbstractNetworkExporter;

	/**
	 * \brief The LightBulbApp.
	 */
	class App : public wxApp
	{
	private:
		/**
		 * \brief Contains all available training plans.
		 */
		std::vector<AbstractTrainingPlan*> trainingPlans;
		std::vector<AbstractNetworkExporter*> exporters;
		std::unique_ptr<NeuralNetworkRepository> neuralNetworkRepository;
		std::unique_ptr<TrainingPlanRepository> trainingPlanRepository;		
		std::unique_ptr<TrainingController> trainingController;		
	public:
		/**
		* \brief Adds a new training plan which should be available in the app.
		* \param trainingPlan The new trianing plan.
		*/
		void addTrainingPlan(AbstractTrainingPlan* trainingPlan);
		void addExporter(AbstractNetworkExporter* exporter);
		// Inherited:
		bool OnInit() override;
		void OnUnhandledException() override;
		bool OnExceptionInMainLoop() override;
	};
}

#endif
