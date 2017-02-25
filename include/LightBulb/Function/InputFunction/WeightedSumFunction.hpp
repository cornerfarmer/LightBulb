#pragma once

#ifndef _WEIGHTEDSUMFUNCTION_H_
#define _WEIGHTEDSUMFUNCTION_H_

// Includes
#include "LightBulb/Function/InputFunction/AbstractInputFunction.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	//Forward declarations
	class Kernel;
	// 
	/**
	 * \brief The WeightedSumFunction uses the weighted sum to calculate the input ;)
	 * \details Describes: \n \n \f$\vec{o} ={\vec{w}}\circ{\vec{a}}\f$ 
	 */
	class WeightedSumFunction : public AbstractInputFunction
	{
	private:
		std::unique_ptr<Kernel> executeKernel;
	public:
		WeightedSumFunction();
		~WeightedSumFunction();
		// Inherited:
		void execute(int layerNr, const std::vector<Vector<>> &activations, std::vector<Vector<>> &netInputs, const std::vector<Matrix<>> &weights, const Vector<>* alternativeActivation = nullptr) const override;
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SINGLE_SERIALIZATION(LightBulb::WeightedSumFunction, LightBulb::AbstractInputFunction, LightBulb);

#endif
