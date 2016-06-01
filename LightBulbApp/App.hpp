#pragma once

#ifndef _APP_H_
#define _APP_H_

#include <wx/wxprec.h>

class AbstractTrainingPlan;

class App : public wxApp
{
private:
	std::vector<AbstractTrainingPlan*> trainingPlans;
public:
	virtual bool OnInit();
	void OnUnhandledException();
	bool OnExceptionInMainLoop();
	void addTrainingPlan(AbstractTrainingPlan* trainingPlan);
};

#endif
