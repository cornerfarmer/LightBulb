#pragma once

#ifndef _ABSTRACTGRADIENTCALCULATION_H_
#define _ABSTRACTGRADIENTCALCULATION_H_

// Includes
#include "IO/UseParentSerialization.hpp"

// Library Includes
#include <vector>
#include <EigenSrc/Dense>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;
	typedef std::vector<Eigen::VectorXd> ErrorMap_t;

	/**
	 * \brief Describes an algorithm which calculates the gradient for an given neural network.
	 */
	class AbstractGradientCalculation
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
		void initGradient(AbstractNetworkTopology* networkTopology);
		/**
		 * \brief Returns the current internal gradient.
		 * \return The internal gradient.
		 */
		std::vector<Eigen::MatrixXd>* getGradient();
		/**
		 * \brief Calculates the gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 * \param errormap The errormap which contains the learning information.
		 */
		virtual void calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap);
		/**
		 * \brief Calculates the gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 * \param errormap The errormap which contains the learning information.
		 * \param gradient The variable which should be used for storing the calculated gradient. (Instead of the internal gradient storage)
		 */
		virtual void calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap, std::vector<Eigen::MatrixXd>& gradient);
		/**
		 * \brief Calculates the gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 * \param netInputs The netInputs which should be used instead of the current ones.
		 * \param activations The activations which should be used instead of the current ones.
		 * \param errormap The errormap which contains the learning information.
		 */
		virtual void calcGradient(AbstractNetworkTopology* networkTopology, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, ErrorMap_t* errormap) = 0;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractGradientCalculation, LightBulb)

#endif

