#pragma once
#ifndef _ABSTRACTMAINAPP_H_
#define _ABSTRACTMAINAPP_H_

// Includes
#include "AbstractApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractSubApp;

	class AbstractMainApp : public AbstractApp
	{
	protected:
	public:
		virtual void removeSubApp(const AbstractSubApp& subApp) = 0;
	};
}

#endif
