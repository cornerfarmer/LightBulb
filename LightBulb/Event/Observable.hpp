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
	/**
	 * \brief Describes an class which can throw events
	 * \tparam EventTypes The event type. Typically an enumaration.
	 * \tparam EventArg The argument type which will be forwarded to the observer
	 */
	template<typename EventTypes, typename EventArg>
	class Observable
	{
	private:
		/**
		 * \brief Holds all observer grouped by the registered event type
		 */
		std::map<EventTypes, std::vector<AbstractObserver<EventArg>*>> observers;
		/**
		 * \brief A mutex which makes sure the observers variable is edited thread safe
		 */
		std::mutex observersMutex;
	protected:
		/**
		 * \brief Throws an event
		 * \param eventType The type of event which should be thrown
		 * \param arg The event argument which will be forwarded to the observers
		 */
		void throwEvent(EventTypes eventType, EventArg& arg)
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

		/**
		 * \brief Returns if the given method and class combination is already registered for the event type.
		 * \tparam Class Implicit param of the class of the given observer object
		 * \param eventType The event type which should be considered
		 * \param observerMethod The method that would be called
		 * \param observerObject The object 
		 * \return Returns if the given object is an observer
		 */
		template<typename Class>
		bool existsObserver(EventTypes eventType, void(Class::*observerMethod)(EventArg&), Class& observerObject)
		{
			for (auto observer = observers[eventType].begin(); observer != observers[eventType].end(); observer++)
			{
				if (dynamic_cast<Observer<Class, EventArg>*>(*observer))
				{
					Observer<Class, EventArg>* castedObserver = dynamic_cast<Observer<Class, EventArg>*>(*observer);
					if (castedObserver->object == &observerObject && castedObserver->method == observerMethod)
					{
						return true;
					}
				}
			}
			return false;
		}

	public:
		virtual ~Observable() {};
		/**
		 * \brief Registeres the given object+method as an new observer for the given event type.
		 * \tparam Class Implicit param of the class of the given observer object
		 * \param eventType The eventType which should be observed
		 * \param observerMethod The method which should be called if the event is thrown
		 * \param observerObject The object on which the method should be called
		 * \note If this observer combination does already exist, this method will have no effect.
		 */
		template<typename Class>
		void registerObserver(EventTypes eventType, void(Class::*observerMethod)(EventArg&), Class& observerObject)
		{
			observersMutex.lock();
			if (!existsObserver(eventType, observerMethod, observerObject))
				observers[eventType].push_back(new Observer<Class, EventArg>(observerMethod, observerObject));
			observersMutex.unlock();
		}

		/**
		 * \brief Removes the observer combination for the given event type
		 * \tparam Class Implicit param of the class of the given observer object
		 * \param eventType The event type which should be considered
		 * \param observerMethod The method from the object which should be removed
		 * \param observerObject The object which should be removed
		 * \note If the observer combination does not exist, this method will have no effect.
		 */
		template<typename Class>
		void removeObserver(EventTypes eventType, void(Class::*observerMethod)(EventArg&), Class& observerObject)
		{
			observersMutex.lock();
			for (auto observer = observers[eventType].begin(); observer != observers[eventType].end(); observer++)
			{
				if (dynamic_cast<Observer<Class, EventArg>*>(*observer))
				{
					Observer<Class, EventArg>* castedObserver = dynamic_cast<Observer<Class, EventArg>*>(*observer);
					if (castedObserver->object == &observerObject && castedObserver->method == observerMethod)
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
