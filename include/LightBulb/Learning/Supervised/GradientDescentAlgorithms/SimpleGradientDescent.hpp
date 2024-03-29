#pragma once

#ifndef _SIMPLEGRADIENTDESCENT_H_
#define _SIMPLEGRADIENTDESCENT_H_

// Library Includes
#include <vector>

// Includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"

namespace LightBulb
{
	class Kernel;

	/**
	* \brief All options for simple gradient descent.
	*/
	struct SimpleGradientDescentOptions : public AbstractGradientDescentAlgorithmOptions
	{
		/**
		 * \brief Sets the weight decay factor, which will be used avoid high weights.
		 * \details Adds the weights multiplicated by this factor to the training error.
		 */
		double weightDecayFac;
		/**
		 * \brief Sets the momentum, which can improve learning speed.
		 * \details Adds the delta weights of the last iteration to the delta weights of the current iteration. This can speed up learning on long plateaus.
		 */
		double momentum;
		/**
		 * \brief Sets the learning rate.
		 * \details Determines how much weights should be changed.
		 */
		double learningRate;
		SimpleGradientDescentOptions()
		{
			weightDecayFac = 0;
			momentum = 0.7f;
			learningRate = 0.45f;
		}
		AbstractCloneable* clone() const override
		{
			return new SimpleGradientDescentOptions(*this);
		}
	};


	/**
	 * \brief Describes a simple basic version of gradient descent with optional weight decay and momentum term.
	 * \details Calculates: \n \n 
	 * \f$\Delta\omega_{t+1} = - \eta f'(\omega_t) + \alpha  \Delta\omega_{t} - \lambda \omega_t\f$ \n \n
	 * \f$\eta: learningRate\f$  \n
	 * \f$\alpha: momentum\f$  \n
	 * \f$\lambda: weight decay factor\f$ \n
	 */
	class SimpleGradientDescent : public AbstractGradientDescentAlgorithm
	{
		template <class Archive>
		friend void serialize(Archive& archive, SimpleGradientDescent& simpleGradientDescent);
		friend struct cereal::LoadAndConstruct<SimpleGradientDescent>;
	private:
		std::unique_ptr<Kernel> simpleGradientDescentKernel;
		std::unique_ptr<Kernel> simpleGradientDescentWithMomentumKernel;
		/**
		 * \brief Contains all previous deltaWeights (used by the momentum term)
		 */
		std::vector<Matrix<>> previousDeltaWeights;
		/**
		* \brief Returns our current options in form of a SimpleGradientDescentOptions object.
		* \return The SimpleGradientDescentOptions object.
		*/
		SimpleGradientDescentOptions& getOptions();
		void kernelSimpleGradientDescent(viennacl::matrix_base<float>& W, const viennacl::matrix_base<float>& G);
		void kernelSimpleGradientDescentWithMomentum(viennacl::matrix_base<float>& W, viennacl::matrix_base<float>& M, const viennacl::matrix_base<float>& G);
		void initializeKernels();
	public:
		/**
		* \brief Creates simple gradient descent.
		* \param options_ The options which configure the RMSprop learning rate.
		*/
		SimpleGradientDescent(SimpleGradientDescentOptions& options_);
		/**
		 * \brief Creates simple gradient descent.
		 */
		SimpleGradientDescent();
		~SimpleGradientDescent();
		SimpleGradientDescent(const SimpleGradientDescent& other) = default;
		SimpleGradientDescent(SimpleGradientDescent&& other) noexcept;
		SimpleGradientDescent& operator=(SimpleGradientDescent other);
		friend void swap(SimpleGradientDescent& lhs, SimpleGradientDescent& rhs) noexcept;

		// Inherited:
		void adjustWeights(const AbstractNetworkTopology& networkTopology, Matrix<>& weights, int layerIndex, const Matrix<>& gradients) override;
		bool learningHasStopped() override;
		void initializeAlgorithm(const AbstractNetworkTopology& networkTopology) override;
		AbstractCloneable* clone() const override;
	};
}

#include "LightBulb/IO/SimpleGradientDescentIO.hpp"

#endif

