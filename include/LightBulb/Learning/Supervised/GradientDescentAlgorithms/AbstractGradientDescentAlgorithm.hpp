#pragma once

#ifndef _ABSTRACTGRADIENTDESCENTALGORITHM_H_
#define _ABSTRACTGRADIENTDESCENTALGORITHM_H_

// Library Includes

// Includes
#include "LightBulb/Learning/AbstractLearningRule.hpp"
#include "LightBulb/Tools/AbstractCloneable.hpp"
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	class AbstractNetworkTopology;

	/**
	 * \brief All general options which are the same for all gradien descent algorithms.
	 */
	struct AbstractGradientDescentAlgorithmOptions : public virtual AbstractCloneable
	{
		/**
		 * \brief Creates the options and fills them with default options.
		 */
		AbstractGradientDescentAlgorithmOptions()
		{
		}
		virtual ~AbstractGradientDescentAlgorithmOptions() {}
	};


	/**
	 * \brief A algorithm which describes how the gradient descent should be executed.
	 * \details The algorithm calculates in every step how the weights should change depend on the calculated gradient.
	 */
	class AbstractGradientDescentAlgorithm : public virtual AbstractCloneable, public virtual AbstractLinearAlgebraUser
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractGradientDescentAlgorithm& gradientDescentAlgorithm);
	private:
		/**
		 * \brief Remembers if the algorithm already has been initialized.
		 */
		bool initialized;
	protected:
		/**
		 * \brief The options which configure the algorithm.
		 */
		std::unique_ptr<AbstractGradientDescentAlgorithmOptions> options;
		/**
		 * \brief The internal initialize function which will be called by initialize().
		 * \param networkTopology The network topology which should be the target for the gradient descent algorithm. 
		 */
		virtual void initializeAlgorithm(const AbstractNetworkTopology& networkTopology) = 0;
	public:
		virtual ~AbstractGradientDescentAlgorithm() {};
		/**
		 * \brief Creates the algorithm.
		 * \param options_ The options which configure the algorithm.
		 */
		AbstractGradientDescentAlgorithm(AbstractGradientDescentAlgorithmOptions* options_);
		AbstractGradientDescentAlgorithm(const AbstractGradientDescentAlgorithm& other);
		friend void swap(AbstractGradientDescentAlgorithm& lhs, AbstractGradientDescentAlgorithm& rhs) noexcept;

		/**
		 * \brief Computes the delta weights for one layer.
		 * \param networkTopology The corresponding network topology.
		 * \param layerIndex The layer nr for which the weight changes should be calculated.
		 * \param gradients The calculated gradient of this layer.
		 * \return The delta weights.
		 */
		virtual void adjustWeights(const AbstractNetworkTopology& networkTopology, Matrix<>& weights, int layerIndex, const Matrix<>& gradients) = 0;
		/**
		 * \brief Returns if the learning has stopped.
		 * \return True if learning has stopped.
		 */
		virtual bool learningHasStopped() = 0;
		/**
		* \brief Initializes the algorithm.
		* \param networkTopology The network topology which should be the target for the gradient descent algorithm.
		* \note This method must be called before the algorithm can be used.
		*/
		void initialize(const AbstractNetworkTopology& networkTopology);
		/**
		 * \brief Returns is the algorithm already has been initialized.
		 * \return True if the algorithm is initialized.
		 */
		bool isInitialized();
	};
}

#include "LightBulb/IO/AbstractGradientDescentAlgorithmIO.hpp"

#endif

