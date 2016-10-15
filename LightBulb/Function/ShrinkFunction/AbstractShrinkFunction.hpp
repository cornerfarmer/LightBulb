#pragma once

#ifndef _ABSTRACTSHRINKFUNCTION_H_
#define _ABSTRACTSHRINKFUNCTION_H_

namespace LightBulb
{
	/**
	 * \brief This abstract class describes a function, which returns a in time shrinking value.
	 */
	class AbstractShrinkFunction
	{
	protected:
		/**
		 * \brief The starting value.
		 */
		double startValue;
		/**
		 * \brief The lowest possible value.
		 */
		double minValue;
	public:
		virtual ~AbstractShrinkFunction() {};
		/**
		 * \brief Create the AbstractShrinkFunction.
		 * \param startValue_ The starting value.
		 * \param minValue_ The lowest possible value.
		 */
		AbstractShrinkFunction(double startValue_, double minValue_);
		/**
		 * \brief Calculate the value in the given timestep.
		 * \param time The timestep.
		 * \return The value at the given timestep.
		 */
		virtual double execute(double time) const = 0;
		/**
		 * \brief Create a copy of the object.
		 * \return The copy
		 */
		virtual AbstractShrinkFunction* getShrinkFunctionCopy() const = 0;
	};
}

#endif