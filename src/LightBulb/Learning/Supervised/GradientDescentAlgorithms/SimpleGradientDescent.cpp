// Includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"

namespace LightBulb
{
	SimpleGradientDescent::SimpleGradientDescent(SimpleGradientDescentOptions& options_)
		:AbstractGradientDescentAlgorithm(new SimpleGradientDescentOptions(options_))
	{
		initializeKernels();
	}

	SimpleGradientDescent::SimpleGradientDescent()
		: AbstractGradientDescentAlgorithm(new SimpleGradientDescentOptions())
	{
		initializeKernels();
	}

	SimpleGradientDescent::~SimpleGradientDescent() = default;

	void SimpleGradientDescent::initializeKernels()
	{
		simpleGradientDescentKernel.reset(new Kernel("simple_gradient_descent", "simple_gradient_descent"));
		simpleGradientDescentWithMomentumKernel.reset(new Kernel("simple_gradient_descent", "simple_gradient_descent_with_momentum"));
	}

	SimpleGradientDescent::SimpleGradientDescent(SimpleGradientDescent&& other) noexcept
		: SimpleGradientDescent()
	{
		swap(*this, other);
	}

	SimpleGradientDescent& SimpleGradientDescent::operator=(SimpleGradientDescent other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(SimpleGradientDescent& lhs, SimpleGradientDescent& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractGradientDescentAlgorithm&>(lhs), static_cast<AbstractGradientDescentAlgorithm&>(rhs));
		swap(lhs.previousDeltaWeights, rhs.previousDeltaWeights);
		swap(lhs.simpleGradientDescentKernel, rhs.simpleGradientDescentKernel);
		swap(lhs.simpleGradientDescentWithMomentumKernel, rhs.simpleGradientDescentWithMomentumKernel);
	}

	SimpleGradientDescentOptions& SimpleGradientDescent::getOptions()
	{
		return static_cast<SimpleGradientDescentOptions&>(*options.get());
	}

	void SimpleGradientDescent::initializeAlgorithm(const AbstractNetworkTopology& networkTopology)
	{
		// If momentum is used
		if (getOptions().momentum > 0)
		{
			// Initialize the learningRates map
			previousDeltaWeights = networkTopology.getAllWeights();
			for (int i = 0; i < previousDeltaWeights.size(); i++)
			{
				previousDeltaWeights[i].getEigenValueForEditing().setZero();
			}
		}
	}

	AbstractCloneable* SimpleGradientDescent::clone() const
	{
		return new SimpleGradientDescent(static_cast<SimpleGradientDescentOptions&>(*options.get()));
	}

	void SimpleGradientDescent::adjustWeights(const AbstractNetworkTopology& networkTopology, Matrix<>& weights, int layerIndex, const Matrix<>& gradients)
	{
		if (isCalculatorType(CT_GPU))
		{
			if (getOptions().momentum > 0)
			{
				kernelSimpleGradientDescentWithMomentum(weights.getViennaclValueForEditing(), previousDeltaWeights[layerIndex - 1].getViennaclValueForEditing(), gradients.getViennaclValue());
			} 
			else
			{
				kernelSimpleGradientDescent(weights.getViennaclValueForEditing(), gradients.getViennaclValue());
			}
		}
		else
		{
			Matrix<> deltaWeight;
			// Calc the delta weight
			deltaWeight.getEigenValueForEditing() = -getOptions().learningRate * gradients.getEigenValue();

			// Substract the weightDecay term
			deltaWeight.getEigenValueForEditing() -= getOptions().weightDecayFac * weights.getEigenValue();

			if (getOptions().momentum > 0) {
				// Add the momentum term
				deltaWeight.getEigenValueForEditing() += getOptions().momentum * previousDeltaWeights[layerIndex - 1].getEigenValue();

				// Set this to the delta weight
				previousDeltaWeights[layerIndex - 1] = deltaWeight;
			}

			weights.getEigenValueForEditing() += deltaWeight.getEigenValue();
		}
	}

	void SimpleGradientDescent::kernelSimpleGradientDescentWithMomentum(viennacl::matrix_base<float>& W, viennacl::matrix_base<float>& M, const viennacl::matrix_base<float>& G)
	{
		viennacl::ocl::enqueue(simpleGradientDescentWithMomentumKernel->use()(
			cl_float(getOptions().learningRate),
			cl_float(getOptions().weightDecayFac),
			cl_float(getOptions().momentum),

			viennacl::traits::opencl_handle(W),
			cl_uint(viennacl::traits::start1(W)), cl_uint(viennacl::traits::start2(W)),
			cl_uint(viennacl::traits::stride1(W)), cl_uint(viennacl::traits::stride2(W)),
			cl_uint(viennacl::traits::size1(W)), cl_uint(viennacl::traits::size2(W)),
			cl_uint(viennacl::traits::internal_size1(W)), cl_uint(viennacl::traits::internal_size2(W)),

			viennacl::traits::opencl_handle(M),
			cl_uint(viennacl::traits::start1(M)), cl_uint(viennacl::traits::start2(M)),
			cl_uint(viennacl::traits::stride1(M)), cl_uint(viennacl::traits::stride2(M)),
			cl_uint(viennacl::traits::size1(M)), cl_uint(viennacl::traits::size2(M)),
			cl_uint(viennacl::traits::internal_size1(M)), cl_uint(viennacl::traits::internal_size2(M)),

			viennacl::traits::opencl_handle(G),
			cl_uint(viennacl::traits::start1(G)), cl_uint(viennacl::traits::start2(G)),
			cl_uint(viennacl::traits::stride1(G)), cl_uint(viennacl::traits::stride2(G)),
			cl_uint(viennacl::traits::internal_size1(G)), cl_uint(viennacl::traits::internal_size2(G))
		));
	}

	void SimpleGradientDescent::kernelSimpleGradientDescent(viennacl::matrix_base<float>& W, const viennacl::matrix_base<float>& G)
	{
		viennacl::ocl::enqueue(simpleGradientDescentKernel->use()(
			cl_float(getOptions().learningRate),
			cl_float(getOptions().weightDecayFac),

			viennacl::traits::opencl_handle(W),
			cl_uint(viennacl::traits::start1(W)), cl_uint(viennacl::traits::start2(W)),
			cl_uint(viennacl::traits::stride1(W)), cl_uint(viennacl::traits::stride2(W)),
			cl_uint(viennacl::traits::size1(W)), cl_uint(viennacl::traits::size2(W)),
			cl_uint(viennacl::traits::internal_size1(W)), cl_uint(viennacl::traits::internal_size2(W)),

			viennacl::traits::opencl_handle(G),
			cl_uint(viennacl::traits::start1(G)), cl_uint(viennacl::traits::start2(G)),
			cl_uint(viennacl::traits::stride1(G)), cl_uint(viennacl::traits::stride2(G)),
			cl_uint(viennacl::traits::internal_size1(G)), cl_uint(viennacl::traits::internal_size2(G))
		));
	}

	bool SimpleGradientDescent::learningHasStopped()
	{
		return false;
	}
}
