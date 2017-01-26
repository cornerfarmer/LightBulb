#pragma once

#ifndef _ABSTRACTGRADIENTCALCULATION_H_
#define _ABSTRACTGRADIENTCALCULATION_H_

// Includes
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/Tools/AbstractCloneable.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

// Library Includes
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;

	/**
	 * \brief Describes an algorithm which calculates the gradient for an given neural network.
	 */
	class AbstractGradientCalculation : public virtual AbstractCloneable, public virtual AbstractLinearAlgebraUser
	{
	private:
		/**
		 * \brief The intern gradient storage.
		 */
		std::vector<Matrix<>> gradient;
	protected:
		/**
		 * \brief Points to the current gradient storage location.
		 * \details Normally this points to the intern gradient, but can also be used to use an extern storage.
		 */
		std::vector<Matrix<>>* gradientToUse;
	public:
		virtual ~AbstractGradientCalculation() {};
		/**
		 * \brief Initializes and/or resets the internal gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 */
		virtual void initGradient(const AbstractNetworkTopology& networkTopology);
		/**
		 * \brief Returns the current internal gradient.
		 * \return The internal gradient.
		 */
		std::vector<Matrix<>>& getGradient();
		/**
		 * \brief Calculates the gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 * \param errorVector The errorVector which contains the learning information.
		 */
		virtual void calcGradient(const AbstractNetworkTopology& networkTopology, const Vector<>& errorVector, const Vector<>* alternativeActivation = nullptr);
		/**
		 * \brief Calculates the gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 * \param errorVector The errorVector which contains the learning information.
		 * \param gradient The variable which should be used for storing the calculated gradient. (Instead of the internal gradient storage)
		 */
		virtual void calcGradient(const AbstractNetworkTopology& networkTopology, const Vector<>& errorVector, std::vector<Matrix<>>& gradient, const Vector<>* alternativeActivation = nullptr);
		/**
		 * \brief Calculates the gradient.
		 * \param networkTopology The network topology whose gradient should be calculated.
		 * \param netInputs The netInputs which should be used instead of the current ones.
		 * \param activations The activations which should be used instead of the current ones.
		 * \param errorVector The errorVector which contains the learning information.
		 */
		virtual void calcGradient(const AbstractNetworkTopology& networkTopology, const std::vector<Vector<>>& netInputs, const std::vector<Vector<>>& activations, const Vector<>& errorVector, const Vector<>* alternativeActivation = nullptr) = 0;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractGradientCalculation, LightBulb)

#endif

