#pragma once

#ifndef _LEARNINGSTATEWINDOW_H_
#define _LEARNINGSTATEWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractWindow.hpp"

// Forward declarations
class LearningStateController;

class LearningStateWindow : public AbstractWindow
{
private:
	wxChoice* trainingPlansChoice;
	LearningStateController* controller;
	void trainingPlanChanged(wxCommandEvent& event);
	void selectionChanged(wxCommandEvent& event);
public:
	LearningStateWindow(LearningStateController* controller_, AbstractWindow* parent = NULL);
	void refreshTrainingPlans();
};

#endif
