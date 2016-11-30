#pragma once
#ifndef _ABSTRACTSUBAPP_H_
#define _ABSTRACTSUBAPP_H_

// Includes
#include "AbstractApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractMainApp;
	/**
	 * \brief Describes a sub app which cannot work independently and has to added to a main app.
	 */
	class AbstractSubApp : public AbstractApp
	{
	protected:
		/**
		 * \brief The corresponding main app.
		 */
		AbstractMainApp* mainApp;
		/**
		 * \brief Prepare the app for closing.
		 */
		virtual void prepareClose() {};
	public:
		/**
		 * \brief Creates the sub app.
		 * \param mainApp_ The corresponding main app.
		 */
		AbstractSubApp(AbstractMainApp& mainApp_);
		/**
		 * \brief Closes the main app.
		 */
		void close();
	};
}

#endif
