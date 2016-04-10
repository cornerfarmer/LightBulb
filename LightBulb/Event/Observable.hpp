#pragma once

#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

// Includes
#include "AbstractObserver.hpp"
#include "Observer.hpp"

//Library includes
#include <map>
#include <vector>

namespace LightBulb
{
	template<typename EventTypes, typename EventArg>
	class Observable
	{
	private:
		std::map<EventTypes, std::vector<AbstractObserver<EventArg>*>> observers;
	protected:
		void throwEvent(EventTypes eventType, EventArg* arg)
		{
			for (auto observer = observers[eventType].begin(); observer != observers[eventType].end(); observer++)
			{
				(*observer)->throwEvent(arg);
			}
		}
	public:
		template<typename Class>
		void registerObserver(EventTypes eventType, void(Class::*observerMethod)(EventArg*), Class* observerObject)
		{
			observers[eventType].push_back(new Observer<Class, EventArg>(observerMethod, observerObject));
		}

		template<typename Class>
		void removeObserver(EventTypes eventType, void(Class::*observerMethod)(EventArg*), Class* observerObject)
		{
			for (auto observer = observers[eventType].begin(); observer != observers[eventType].end(); observer++)
			{
				if (dynamic_cast<Observer<Class, EventArg>*>(*observer))
				{
					Observer<Class, EventArg>* castedObserver = dynamic_cast<Observer<Class, EventArg>*>(*observer);
					if (castedObserver->object == observerObject && castedObserver->method == observerMethod)
					{
						observers[eventType].erase(observer);
						break;
					}
				}
			}
		}
	};
}

#endif
