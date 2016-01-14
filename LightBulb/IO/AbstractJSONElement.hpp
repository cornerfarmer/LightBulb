#pragma once

#ifndef _ABSTRACTJSONELEMENT_H_
#define _ABSTRACTJSONELEMENT_H_

// Library includes
#include <string>

// Forward declarations

// 
class AbstractJSONElement
{
private:
public:
	virtual std::string toString() = 0;
};

#endif