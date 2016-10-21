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

	class AbstractSubAppFactory
	{
	protected:
	public:
		virtual ~AbstractSubAppFactory() {};
		virtual AbstractSubApp* createSupApp(AbstractMainApp& mainApp, AbstractWindow* parent = nullptr) const = 0;
		virtual std::string getLabel() const = 0;
	};
}

#endif
