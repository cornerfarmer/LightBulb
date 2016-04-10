#pragma once

#ifndef _ABSTRACTSUBAPPFACTORY_H_
#define _ABSTRACTSUBAPPFACTORY_H_

// Library includes
#include <cstddef>
#include <string>

// Includes

// Forward declarations
class AbstractSubApp;
class AbstractWindow;

class AbstractSubAppFactory
{
protected:
public:
	virtual AbstractSubApp* createWindow(AbstractWindow* parent = NULL) = 0;
	virtual std::string getLabel() = 0;
};

#endif
