#pragma once
#ifndef _ABSTRACTSUBAPP_H_
#define _ABSTRACTSUBAPP_H_

// Includes
#include "AbstractApp.hpp"

// Forward declarations
class AbstractMainApp;

class AbstractSubApp : public AbstractApp
{
protected:
	AbstractMainApp* mainApp;
	virtual void prepareClose() {};
public:	
	AbstractSubApp(AbstractMainApp* mainApp_);
	void close();
};

#endif
