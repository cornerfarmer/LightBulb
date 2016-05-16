#pragma once

#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

// Includes
#include "AbstractObserver.hpp"
#include "Observer.hpp"

//Library includes
#include <map>
#include <vector>
#include <mutex>

namespace LightBulb
{
	template<typename EventTypes, typename EventArg>
	class Observable
	{
	private:
		std::map<EventTypes, std::vector<AbstractObserver<EventArg>*>> observers;
		std::mutex observersMutex;
	protected:
		void throwEvent(EventTypes eventType, EventArg* arg)
		{
			if (observers.size() == 0)
				return;
			observersMutex.lock();
			for (auto observer = observers[eventType].begin(); observer != observers[eventType].end(); )
			{
				try
				{
					(*observer)->throwEvent(arg);
					observer++;
				}
				catch(...)
				{
					observer = observers[eventType].erase(observer);
				}
			}
			observersMutex.unlock();
		}

		template<typename Class>
		bool existsObserver(EventTypes eventType, void(Class::*observerMethod)(EventArg*), Class* observerObject)
		{
			for (auto observer = observers[eventType].begin(); observer != observers[eventType].end(); observer++)
			{
				if (dynamic_cast<Observer<Class, EventArg>*>(*observer))
				{
					Observer<Class, EventArg>* castedObserver = dynamic_cast<Observer<Class, EventArg>*>(*observer);
					if (castedObserver->object == observerObject && castedObserver->method == observerMethod)
					{
						return true;
					}
				}
			}
			return false;
		}

	public:
		template<typename Class>
		void registerObserver(EventTypes eventType, void(Class::*observerMethod)(EventArg*), Class* observerObject)
		{
			observersMutex.lock();
			if (!existsObserver(eventType, observerMethod, observerObject))
				observers[eventType].push_back(new Observer<Class, EventArg>(observerMethod, observerObject));
			observersMutex.unlock();
		}

		template<typename Class>
		void removeObserver(EventTypes eventType, void(Class::*observerMethod)(EventArg*), Class* observerObject)
		{
			observersMutex.lock();
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
			observersMutex.unlock();
		}
	};
}

#endif
