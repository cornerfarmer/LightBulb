#pragma once

#ifndef _TRAININGWINDOW_H_
#define _TRAININGWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Graphics/AbstractWindow.hpp"
#include "TrainingController.hpp"

// Forward declarations


class TrainingWindow : public AbstractWindow
{
private:
	std::unique_ptr<TrainingController> controller;
	wxPanel* createNNColumn(wxWindow* parent);
	wxPanel* createTrainingColumn(wxWindow* parent);
	wxPanel* createRunningTrainingColumn(wxWindow* parent);
	wxPanel* createDetailsPanel(wxWindow* parent);
	void createMenuBar();
protected:
	DECLARE_EVENT_TABLE();
public:
	TrainingWindow();
	void OnClick(wxCommandEvent& event);
};

#endif
