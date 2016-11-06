#pragma once
#ifndef _ABSTRACTMAINAPP_H_
#define _ABSTRACTMAINAPP_H_

// Includes
#include "AbstractApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractSubApp;
	/**
	 * \brief Describes an app which is fully independent and acts as main app.
	 */
	class AbstractMainApp : public AbstractApp
	{
	protected:
	public:
		/**
		 * \brief Removes a active sub app.
		 * \param subApp The sub app to remove.
		 */
		virtual void removeSubApp(const AbstractSubApp& subApp) = 0;
	};
}

#endif
