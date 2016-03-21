#pragma once

#ifndef _TRAININGWINDOW_H_
#define _TRAININGWINDOW_H_

// Includes
#include "Graphics/AbstractWindow.hpp"

// Forward declarations

// A chart which shows the location of neurons
class TrainingWindow : public AbstractWindow
{
protected:
	DECLARE_EVENT_TABLE();
public:
	TrainingWindow();
	void OnClick(wxCommandEvent& event);
};

#endif
