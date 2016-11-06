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
	/**
	 * \brief A single window.
	 */
	class AbstractWindow : public wxFrame
	{
	protected:
		/**
		 * \brief The corresponding controller.
		 */
		AbstractApp* controller;
		/**
		 * \brief Recalculates the layout of the given sizer.
		 * \param sizer The sizer to refresh.
		 */
		void refreshAfterChange(wxSizer& sizer);
	public:
		/**
		 * \brief Creates the window.
		 * \param controller_ The corresponding controller.
		 * \param label The label of the window.
		 * \param parent Optional: A parent window.
		 */
		AbstractWindow(AbstractApp& controller_, const std::string& label, AbstractWindow* parent = nullptr);
	};
}

#endif
