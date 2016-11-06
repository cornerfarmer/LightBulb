#pragma once

#ifndef _ABSTRACTINPUTFUNCTION_H_
#define _ABSTRACTINPUTFUNCTION_H_

// Includes
#include "Tools/AbstractCloneable.hpp"
#include <memory>
#include "EigenSrc/Dense"
#include <vector>

// Forward declarations

namespace LightBulb
{
	/**
	 * \brief An InputFunction calculates one input value from the output of all previous connected neurons
	 */
	class AbstractInputFunction : public virtual AbstractCloneable
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
		virtual void execute(int layerNr, const std::vector<Eigen::VectorBlock<Eigen::VectorXd>> &activations, std::vector<Eigen::VectorXd> &netInputs, const std::vector<Eigen::MatrixXd> &weights) const = 0;
	};
}

#endif