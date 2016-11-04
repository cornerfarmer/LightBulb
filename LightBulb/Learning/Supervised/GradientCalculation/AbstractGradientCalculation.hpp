#pragma once

#ifndef _ABSTRACTGRADIENTCALCULATION_H_
#define _ABSTRACTGRADIENTCALCULATION_H_

// Includes
#include "IO/UseParentSerialization.hpp"
#include "Tools/AbstractCloneable.hpp"

// Library Includes
#include <vector>
#include <EigenSrc/Dense>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;

	/**
	 * \brief Describes an algorithm which calculates the gradient for an given neural network.
	 */
	class AbstractGradientCalculation : public virtual AbstractCloneable
	{
	private:
		/**
		 * \brief The intern gradient storage.
		 */
		std::vector<Eigen::MatrixXd> gradient;
	protected:
		/**
		 * \brief Points to the current gradient storage location.
		 * \details Normally this points to the intern gradient, but can also be used to use an extern storage.
		 */
		std::vector<Eigen::MatrixXd>* gradientToUse;
	public:
		virtual ~AbstractGradientCalculation() {};
		/**
		 * \brief Initializes and/or resets the internal gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 */
		void initGradient(const AbstractNetworkTopology& networkTopology);
		/**
		 * \brief Returns the current internal gradient.
		 * \return The internal gradient.
		 */
		std::vector<Eigen::MatrixXd>& getGradient();
		/**
		 * \brief Calculates the gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 * \param errorVector The errorVector which contains the learning information.
		 */
		virtual void calcGradient(const AbstractNetworkTopology& networkTopology, const Eigen::VectorXd& errorVector);
		/**
		 * \brief Calculates the gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 * \param errorVector The errorVector which contains the learning information.
		 * \param gradient The variable which should be used for storing the calculated gradient. (Instead of the internal gradient storage)
		 */
		virtual void calcGradient(const AbstractNetworkTopology& networkTopology, const Eigen::VectorXd& errorVector, std::vector<Eigen::MatrixXd>& gradient);
		/**
		 * \brief Calculates the gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 * \param netInputs The netInputs which should be used instead of the current ones.
		 * \param activations The activations which should be used instead of the current ones.
		 * \param errorVector The errorVector which contains the learning information.
		 */
		virtual void calcGradient(const AbstractNetworkTopology& networkTopology, const std::vector<Eigen::VectorXd>& netInputs, const std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, const Eigen::VectorXd& errorVector) = 0;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractGradientCalculation, LightBulb)

#endif

