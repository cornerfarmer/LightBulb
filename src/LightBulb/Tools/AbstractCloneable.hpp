#pragma once

#ifndef _ABSTRACTCLONEABLE_H_
#define _ABSTRACTCLONEABLE_H_

// Includes

// Library includes

namespace LightBulb
{
	class AbstractCloneable
	{
	private:
	public:
		virtual ~AbstractCloneable() {}
		virtual AbstractCloneable* clone() const = 0;
	};
}

#endif
