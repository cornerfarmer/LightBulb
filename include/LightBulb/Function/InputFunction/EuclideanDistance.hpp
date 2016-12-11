#pragma once

#ifndef _EUCLIDEANDISTANCEFUNCTION_H_
#define _EUCLIDEANDISTANCEFUNCTION_H_

// Includes
#include "LightBulb/Function/InputFunction/AbstractInputFunction.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

//Forward declarations

namespace LightBulb
{
	/**
	 * \brief The EuclideanDistance calculates the distance between the input and the center of a RBF Neuron (weights)
	 * \details Describes: \n \n \f$o=\sqrt{\sum{(\vec{w} - \vec{a})^2}}\f$ \n \n
	 */
	class EuclideanDistance : public AbstractInputFunction
	{
	private:
	public:
		// Inherited:
		void execute(int layerNr, const std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, std::vector<Eigen::VectorXd>& netInputs, const std::vector<Eigen::MatrixXd>& weights) const override;
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SINGLE_SERIALIZATION(LightBulb::EuclideanDistance, LightBulb::AbstractInputFunction, LightBulb);

#endif
