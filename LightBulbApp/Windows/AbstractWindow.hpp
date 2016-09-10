#pragma once

#ifndef _ABSTRACTWINDOW_H_
#define _ABSTRACTWINDOW_H_

// Includes
#include <list>
#include <wx/wxprec.h>

namespace LightBulb
{
	// Forward declarations
	class AbstractApp;

	// A chart which shows the location of neurons
	class AbstractWindow : public wxFrame
	{
	protected:
		AbstractApp* controller;
		void refreshAfterChange(wxSizer* sizer);
	public:
		AbstractWindow(AbstractApp* controller_, std::string label, AbstractWindow* parent = NULL);
	};
}

#endif
