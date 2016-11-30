#pragma once

#ifndef _ABSTRACTSUBAPPFACTORY_H_
#define _ABSTRACTSUBAPPFACTORY_H_

// Library includes
#include <cstddef>
#include <string>

// Includes

namespace LightBulb
{
	// Forward declarations
	class AbstractSubApp;
	class AbstractWindow;
	class AbstractMainApp;
	/**
	 * \brief A sub app factory.
	 */
	class AbstractSubAppFactory
	{
	protected:
	public:
		virtual ~AbstractSubAppFactory() {};
		/**
		 * \brief Creates a sub app.
		 * \param mainApp The main app which should control the sub app.
		 * \param parent The parent window.
		 * \return The new sub app.
		 */
		virtual AbstractSubApp* createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const = 0;
		/**
		 * \brief Returns the label of the sub app.
		 * \return The label.
		 */
		virtual std::string getLabel() const = 0;
	};
}

#endif
