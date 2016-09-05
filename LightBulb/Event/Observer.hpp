#pragma once

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// Includes
#include "AbstractObserver.hpp"

//Library includes

namespace LightBulb
{
	/**
	 * \brief The default observer which just consists of one object.
	 * \tparam Class The class of the observer object
	 * \tparam EventArg The event argument
	 */
	template<typename Class, typename EventArg>
	class Observer : public AbstractObserver<EventArg>
	{
	private:
	public:
		/**
		 * \brief Holds the method which should be called.
		 */
		void (Class::*method)(EventArg*);
		/**
		 * \brief The target object
		 */
		Class* object;
		/**
		 * \brief Creates an observer for the given object and the specified method
		 * \param method_ The method to call
		 * \param object_ The target object
		 */
		Observer(void(Class::*method_)(EventArg*), Class* object_)
		{
			method = method_;
			object = object_;
		}

		/**
		 * \brief Calls the specified method of the object
		 * \param arg The argument which will be forwarded to the object
		 */
		void throwEvent(EventArg* arg) override
		{
			(object->*method)(arg);
		}
	};
}

#endif
