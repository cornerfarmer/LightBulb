#pragma once

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// Includes
#include "AbstractObserver.hpp"

//Library includes

template<typename Class, typename EventArg>
class Observer : public AbstractObserver<EventArg>
{
private:
public:
	void (Class::*method)(EventArg*);
	Class* object;

	Observer(void(Class::*method_)(EventArg*), Class* object_)
	{
		method = method_;
		object = object_;
	}

	void throwEvent(EventArg* arg)
	{
		(object->*method)(arg);
	}
};

#endif
