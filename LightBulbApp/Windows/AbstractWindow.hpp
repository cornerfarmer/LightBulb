#pragma once

#ifndef _ABSTRACTWINDOW_H_
#define _ABSTRACTWINDOW_H_

// Includes
#include <list>
#include <wx/wxprec.h>

// Forward declarations

// A chart which shows the location of neurons
class AbstractWindow : public wxFrame
{
protected:
	void refreshAfterChange(wxSizer* sizer);
public:
	AbstractWindow(std::string label, AbstractWindow* parent = NULL);
	
};

#endif
