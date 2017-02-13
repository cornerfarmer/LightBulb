#pragma once

#ifndef _ABSTRACTTEACHINGLESSON_H_
#define _ABSTRACTTEACHINGLESSON_H_

// Library Includes
#include <vector>

// Includes
#include "LightBulb/Teaching/TeachingInput.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	class AbstractActivationOrder;
	class AbstractActivationFunction;
	class AbstractNeuron;
	class StandardNeuron;

	/**
	 * \brief Describes a teaching lesson which stores an input and the preferred output.
	 */
	class AbstractTeachingLesson : public virtual AbstractLinearAlgebraUser
	{
	private:
		mutable Vector<> errorVector;
		mutable Scalar<> specificErrorScalar;
		void calcErrorVector(viennacl::vector<float>& errorVector, const viennacl::vector<float>& teachingInput, const viennacl::vector<float>& outputVector) const;
		void calcSpecificError(viennacl::scalar<float>& specificError, viennacl::vector<float>& errorVector) const;
	public:
		virtual ~AbstractTeachingLesson() {}
		/**
		 * \brief Put the teachingPattern into the neuralNetwork and refreshes the network.
		 * \param neuralNetwork The neural network to evaluate.
		 * \param activationOrder The activation order to use.
		 * \return The output values.
		 */
		const Vector<>& tryLesson(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder) const;
		/**
		 * \brief Returns the teaching input as a double vector.
		 * \param activationFunction The activation function the target network uses in the output layer.
		 * \return The teaching input.
		 */
		virtual const TeachingInput<>& getTeachingInput(const AbstractActivationFunction& activationFunction) const = 0;
		/**
		 * \brief Returns the teaching pattern.
		 * \return The teaching pattern.
		 */
		virtual const Vector<>& getTeachingPattern() const = 0;
		/**
		 * \brief Calculates the error vector, which contains the error (target - current) for every output neuron.
		 * \param neuralNetwork The neural network to evaluate.
		 * \param activationOrder The activation order to use.
		 * \param clipError Determines if the error should be clipped between -1 and 1.
		 * \return The error vector.
		 */
		const Vector<>& getErrorVector(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder, bool clipError = false) const;
		/**
		 * \brief Returns the error vector from the given output vector.
		 * \param outputVector The output vector from the neural network when using the teaching lessons pattern as input.
		 * \param neuralNetwork The neural network which was used for the calculation.
		 * \param clipError Determines if the error should be clipped between -1 and 1.
		 * \return The error vector.
		 */
		virtual void getErrorVectorFromOutputVector(const Vector<>& outputVector, AbstractNeuralNetwork& neuralNetwork, bool clipError = false) const;
		/**
		 * \brief Calculates the specific error of the given network when using this lesson.
		 * \details \f$ E=0.5*\sum{(t_i-y_i)^2} \f$
		 * \param neuralNetwork The network to evaluate.
		 * \param activationOrder The activation order to use.
		 * \param clipError Determines if the error should be clipped between -1 and 1.
		 * \return The specific error.
		 */
		virtual double getSpecificError(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder, bool clipError = false) const;
	};
}

#endif

