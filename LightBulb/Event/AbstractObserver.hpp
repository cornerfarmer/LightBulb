#pragma once

#ifndef _ABSTRACTOBSERVER_H_
#define _ABSTRACTOBSERVER_H_

// Includes

//Library includes

template<typename EventArg>
class AbstractObserver
{
private:
public:
	virtual void throwEvent(EventArg* arg) = 0;
};

#endif
