﻿#pragma once

#ifndef _WEIGHTEDSUMFUNCTION_H_
#define _WEIGHTEDSUMFUNCTION_H_

// Includes
#include "LightBulb/Function/InputFunction/AbstractInputFunction.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	//Forward declarations
	class Edge;

	// 
	/**
	 * \brief The WeightedSumFunction uses the weighted sum to calculate the input ;)
	 * \details Describes: \n \n \f$\vec{o} ={\vec{w}}\circ{\vec{a}}\f$ 
	 */
	class WeightedSumFunction : public AbstractInputFunction
	{
	private:
	public:
		// Inherited:
		void execute(int layerNr, const std::vector<Eigen::VectorBlock<Eigen::VectorXd>> &activations, std::vector<Eigen::VectorXd> &netInputs, const std::vector<Eigen::MatrixXd> &weights) const override;
		AbstractCloneable* clone() const override;
	};
}

EMPTY_CHILD_SERIALIZATION(LightBulb::WeightedSumFunction, LightBulb);

#endif