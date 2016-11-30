#pragma once

#ifndef _ABSTRACTCLONEABLE_H_
#define _ABSTRACTCLONEABLE_H_

// Includes

// Library includes

namespace LightBulb
{
	/**
	 * \brief Describes a class which can be cloned.
	 */
	class AbstractCloneable
	{
	private:
	public:
		virtual ~AbstractCloneable() {}
		/**
		 * \brief Clones the object. (Deep clone)
		 * \return The cloned object.
		 */
		virtual AbstractCloneable* clone() const = 0;
	};
}

#endif
