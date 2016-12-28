// Includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

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

	Matrix RMSPropLearningRate::calcDeltaWeight(const AbstractNetworkTopology& networkTopology, int layerIndex, const Matrix& gradients)
	{
		prevGradient[layerIndex - 1].getEigenValueForEditing() = getOptions().gradientMomentum * prevGradient[layerIndex - 1].getEigenValue() + (1 - getOptions().gradientMomentum) * gradients.getEigenValue();
		prevSquaredGradient[layerIndex - 1].getEigenValueForEditing() = getOptions().squaredGradientMomentum * prevSquaredGradient[layerIndex - 1].getEigenValue() + (1 - getOptions().squaredGradientMomentum) * gradients.getEigenValue().cwiseAbs2();

		prevDeltaWeights[layerIndex - 1].getEigenValueForEditing() = getOptions().deltaWeightsMomentum * prevDeltaWeights[layerIndex - 1].getEigenValue() - getOptions().learningRate * gradients.getEigenValue().cwiseQuotient(((prevSquaredGradient[layerIndex - 1].getEigenValue().array() - prevGradient[layerIndex - 1].getEigenValue().cwiseAbs2().array() + getOptions().minSquaredGradient).cwiseSqrt()).matrix());

		return prevDeltaWeights[layerIndex - 1];
	}


	bool RMSPropLearningRate::learningHasStopped()
	{
		return false;
	}
}

