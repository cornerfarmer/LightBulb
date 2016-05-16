#pragma once
#ifndef _ABSTRACTMAINAPP_H_
#define _ABSTRACTMAINAPP_H_

// Includes
#include "AbstractApp.hpp"

// Forward declarations
class AbstractSubApp;

class AbstractMainApp : public AbstractApp
{
protected:
public:	
	virtual void removeSubApp(AbstractSubApp* subApp) = 0;
};

#endif
