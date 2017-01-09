#pragma once

#ifndef _ABSTRACTINPUTFUNCTION_H_
#define _ABSTRACTINPUTFUNCTION_H_

// Includes
#include "LightBulb/Tools/AbstractCloneable.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include <memory>
#include <vector>

// Forward declarations

namespace LightBulb
{
	class Matrix;
	class Vector;

	/**
	 * \brief An InputFunction calculates one input value from the output of all previous connected neurons
	 */
	class AbstractInputFunction : public virtual AbstractCloneable, public virtual AbstractLinearAlgebraUser
	{
	private:
	public:
		virtual ~AbstractInputFunction() {}
		/**
		 * \brief Calculates the netInputs for layer "layerNr" from activations and weights from layer "layerNr - 1".
		 * \param layerNr The number of the layer for which the inputs should be calculated for
		 * \param activations The activations which will be used to calculate the inputs
		 * \param netInputs The variable where the calculated inputs will be stored in
		 * \param weights The weights which will be used to calculate the inputs
		 */
		virtual void execute(int layerNr, const std::vector<Vector> &activations, std::vector<Vector> &netInputs, const std::vector<Matrix> &weights) const = 0;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractInputFunction, LightBulb);

#endif