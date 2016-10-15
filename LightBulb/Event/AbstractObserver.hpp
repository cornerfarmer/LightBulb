#pragma once

#ifndef _ABSTRACTOBSERVER_H_
#define _ABSTRACTOBSERVER_H_

// Includes

//Library includes

namespace LightBulb
{
	/**
	 * \brief Reacts on thrown events
	 * \tparam EventArg The argument type of the thrown event
	 */
	template<typename EventArg>
	class AbstractObserver
	{
	private:
	public:
		virtual ~AbstractObserver() {};
		/**
		 * \brief This method is called if the corresponding observable object throws the registered event.
		 * \param arg The event argument
		 */
		virtual void throwEvent(EventArg* arg) = 0;
	};
}

#endif
