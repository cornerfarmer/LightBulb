#pragma once

#ifndef _WEIGHTEDSUMFUNCTION_H_
#define _WEIGHTEDSUMFUNCTION_H_

// Includes
#include "Function/InputFunction/AbstractInputFunction.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	//Forward declarations
	class Edge;

	// 
	/**
	 * \brief The WeightedSumFunction uses the weighted sum to calculate the input ;)
	 * \details Describes: \n \n \f$\vec{o} ={\vec{w}}\circ{\vec{a}}\f$ \n \n
	 */
	class WeightedSumFunction : public AbstractInputFunction
	{
	private:
	public:
		// Inherited:
		void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>> &activations, std::vector<Eigen::VectorXd> &netInputs, std::vector<Eigen::MatrixXd> &weights) override;
		AbstractInputFunction* getInputFunctionCopy() override;
	};
}

EMPTY_CHILD_SERIALIZATION(LightBulb::WeightedSumFunction, LightBulb);

#endif
