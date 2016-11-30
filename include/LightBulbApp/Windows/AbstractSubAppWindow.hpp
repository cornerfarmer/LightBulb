#pragma once

#ifndef _ABSTRACTSUBAPPWINDOW_H_
#define _ABSTRACTSUBAPPWINDOW_H_

// Includes
#include <list>
#include <wx/wxprec.h>
#include "AbstractWindow.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractSubApp;
	/**
	 * \brief A window for a sub app.
	 */
	class AbstractSubAppWindow : public AbstractWindow
	{
	private:
		/**
		 * \brief Returns the controller of the window.
		 * \return The controller.
		 */
		AbstractSubApp* getController();
	protected:
		/**
		 * \brief Listener for a window close event.
		 * \param event The close event.
		 */
		virtual void close(wxCloseEvent& event);
	public:
		/**
		 * \brief Creates the window.
		 * \param controller_ The corresponding controller.
		 * \param label The label of the window.
		 * \param parent The parent window.
		 */
		AbstractSubAppWindow(AbstractSubApp& controller_, std::string label, AbstractWindow& parent);
	};
}

#endif
