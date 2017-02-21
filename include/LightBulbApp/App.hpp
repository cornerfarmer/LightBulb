#pragma once

#ifndef _APP_H_
#define _APP_H_

// Includes

// Library includes
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <memory>
#include <vector>

namespace LightBulb
{
	class AbstractTrainingPlan;
	class NeuralNetworkRepository;
	class TrainingPlanRepository;
	class TrainingController;
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
		std::unique_ptr<NeuralNetworkRepository> neuralNetworkRepository;
		std::unique_ptr<TrainingPlanRepository> trainingPlanRepository;		
		std::unique_ptr<TrainingController> trainingController;		
	public:
		~App();
		App();
		/**
		* \brief Adds a new training plan which should be available in the app.
		* \param trainingPlan The new trianing plan.
		*/
		void addTrainingPlan(AbstractTrainingPlan* trainingPlan);
		// Inherited:
		bool OnInit() override;
		void OnUnhandledException() override;
		bool OnExceptionInMainLoop() override;
	};
}

#endif
