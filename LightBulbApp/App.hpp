#pragma once

#ifndef _APP_H_
#define _APP_H_

#include <wx/wxprec.h>

namespace LightBulb
{
	class AbstractTrainingPlan;

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
	public:
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
