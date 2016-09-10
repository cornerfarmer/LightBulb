#pragma once

#ifndef _APP_H_
#define _APP_H_

#include <wx/wxprec.h>

namespace LightBulb
{
	class AbstractTrainingPlan;

	class App : public wxApp
	{
	private:
		std::vector<AbstractTrainingPlan*> trainingPlans;
	public:
		bool OnInit() override;
		void OnUnhandledException() override;
		bool OnExceptionInMainLoop() override;
		void addTrainingPlan(AbstractTrainingPlan* trainingPlan);
	};
}

#endif
