#pragma once

#ifndef _ABSTRACTSUBAPPWINDOW_H_
#define _ABSTRACTSUBAPPWINDOW_H_

// Includes
#include <list>
#include <wx/wxprec.h>
#include "AbstractWindow.hpp"

// Forward declarations
class AbstractSubApp;

// A chart which shows the location of neurons
class AbstractSubAppWindow : public AbstractWindow
{
private:
	AbstractSubApp* getController();
protected:
	virtual void close(wxCloseEvent& event);
public:
	AbstractSubAppWindow(AbstractSubApp* controller_, std::string label, AbstractWindow* parent);
	
};

#endif
