// Includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

namespace LightBulb
{
	RMSPropLearningRate::RMSPropLearningRate(RMSPropLearningRateOptions& options_)
		: AbstractGradientDescentAlgorithm(new RMSPropLearningRateOptions(options_))
	{
	}

	RMSPropLearningRate::RMSPropLearningRate()
		: AbstractGradientDescentAlgorithm(new RMSPropLearningRateOptions())
	{
	}

	RMSPropLearningRate::RMSPropLearningRate(RMSPropLearningRate&& other) noexcept
		: RMSPropLearningRate()
	{
		swap(*this, other);
	}


	RMSPropLearningRate& RMSPropLearningRate::operator=(RMSPropLearningRate other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(RMSPropLearningRate& lhs, RMSPropLearningRate& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractGradientDescentAlgorithm&>(lhs), static_cast<AbstractGradientDescentAlgorithm&>(rhs));
		swap(lhs.prevGradient, rhs.prevGradient);
		swap(lhs.prevSquaredGradient, rhs.prevSquaredGradient);
		swap(lhs.prevDeltaWeights, rhs.prevDeltaWeights);
	}

	RMSPropLearningRateOptions& RMSPropLearningRate::getOptions()
	{
		return static_cast<RMSPropLearningRateOptions&>(*options.get());
	}

	void RMSPropLearningRate::initializeAlgorithm(const AbstractNetworkTopology& networkTopology)
	{
		// Make sure the previous learning rates map is empty
		prevGradient.resize(networkTopology.getAllWeights().size());
		for (int i = 0; i < prevGradient.size(); i++)
		{
			prevGradient[i].getEigenValueForEditing().resizeLike(networkTopology.getAllWeights().at(i).getEigenValue());
			prevGradient[i].getEigenValueForEditing().setZero();
		}
		prevSquaredGradient = prevGradient;
		prevDeltaWeights = prevGradient;
	}

	AbstractCloneable* RMSPropLearningRate::clone() const
	{
		return new RMSPropLearningRate(*this);
	}

	void RMSPropLearningRate::adjustWeights(const AbstractNetworkTopology& networkTopology, Matrix<>& weights, int layerIndex, const Matrix<>& gradients)
	{
		if (isCalculatorType(CT_GPU))
		{
			static viennacl::ocl::kernel& kernel = getKernel("rms_prop_learning_rate", "rms_prop_learning_rate", "rms_prop_learning_rate.cl");

			viennacl::ocl::enqueue(kernel(
				viennacl::traits::opencl_handle(prevSquaredGradient[layerIndex - 1].getViennaclValueForEditing()),
				cl_uint(viennacl::traits::internal_size2(prevSquaredGradient[layerIndex - 1].getViennaclValue())),
				viennacl::traits::opencl_handle(prevDeltaWeights[layerIndex - 1].getViennaclValueForEditing()),
				cl_uint(viennacl::traits::internal_size2(prevDeltaWeights[layerIndex - 1].getViennaclValue())),
				viennacl::traits::opencl_handle(prevGradient[layerIndex - 1].getViennaclValueForEditing()),
				cl_uint(viennacl::traits::internal_size2(prevGradient[layerIndex - 1].getViennaclValue())),
				viennacl::traits::opencl_handle(weights.getViennaclValueForEditing()),
				cl_uint(viennacl::traits::internal_size2(weights.getViennaclValue())),
				viennacl::traits::opencl_handle(gradients.getViennaclValue()),
				cl_uint(viennacl::traits::internal_size2(gradients.getViennaclValue())),
				cl_uint(viennacl::traits::size1(weights.getViennaclValue())),
				cl_uint(viennacl::traits::size2(weights.getViennaclValue())),
				cl_float(getOptions().gradientMomentum),
				cl_float(getOptions().deltaWeightsMomentum),
				cl_float(getOptions().squaredGradientMomentum),
				cl_float(getOptions().learningRate),
				cl_float(getOptions().minSquaredGradient)
			));
		}
		else
		{
			prevGradient[layerIndex - 1].getEigenValueForEditing() = getOptions().gradientMomentum * prevGradient[layerIndex - 1].getEigenValue() + (1 - getOptions().gradientMomentum) * gradients.getEigenValue();
			prevSquaredGradient[layerIndex - 1].getEigenValueForEditing() = getOptions().squaredGradientMomentum * prevSquaredGradient[layerIndex - 1].getEigenValue() + (1 - getOptions().squaredGradientMomentum) * gradients.getEigenValue().cwiseAbs2();

			prevDeltaWeights[layerIndex - 1].getEigenValueForEditing() = getOptions().deltaWeightsMomentum * prevDeltaWeights[layerIndex - 1].getEigenValue() - getOptions().learningRate * gradients.getEigenValue().cwiseQuotient(((prevSquaredGradient[layerIndex - 1].getEigenValue().array() - prevGradient[layerIndex - 1].getEigenValue().cwiseAbs2().array() + getOptions().minSquaredGradient).cwiseSqrt()).matrix());

			weights.getEigenValueForEditing() += prevDeltaWeights[layerIndex - 1].getEigenValue();
		}
	}


	bool RMSPropLearningRate::learningHasStopped()
	{
		return false;
	}
}

