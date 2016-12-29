// Includes
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

namespace LightBulb
{
	SimpleGradientDescent::SimpleGradientDescent(SimpleGradientDescentOptions& options_)
		:AbstractGradientDescentAlgorithm(new SimpleGradientDescentOptions(options_))
	{

	}

	SimpleGradientDescent::SimpleGradientDescent()
		: AbstractGradientDescentAlgorithm(new SimpleGradientDescentOptions())
	{
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
		return new SimpleGradientDescent(*this);
	}

	Matrix SimpleGradientDescent::calcDeltaWeight(const AbstractNetworkTopology& networkTopology, int layerIndex, const Matrix& gradients)
	{
		Matrix deltaWeight;

		if (deltaWeight.getCalculatorType() == CT_GPU)
		{
			// Calc the delta weight
			deltaWeight.getViennaclValueForEditing() = -getOptions().learningRate * gradients.getViennaclValue();

			// Substract the weightDecay term
			deltaWeight.getViennaclValueForEditing() -= getOptions().weightDecayFac * networkTopology.getAfferentWeightsPerLayer(layerIndex).getViennaclValue();

			if (getOptions().momentum > 0) {
				// Add the momentum term
				deltaWeight.getViennaclValueForEditing() += getOptions().momentum * previousDeltaWeights[layerIndex - 1].getViennaclValue();

				// Set this to the delta weight
				previousDeltaWeights[layerIndex - 1] = deltaWeight;
			}
		}
		else
		{
			// Calc the delta weight
			deltaWeight.getEigenValueForEditing() = -getOptions().learningRate * gradients.getEigenValue();

			// Substract the weightDecay term
			deltaWeight.getEigenValueForEditing() -= getOptions().weightDecayFac * networkTopology.getAfferentWeightsPerLayer(layerIndex).getEigenValue();

			if (getOptions().momentum > 0) {
				// Add the momentum term
				deltaWeight.getEigenValueForEditing() += getOptions().momentum * previousDeltaWeights[layerIndex - 1].getEigenValue();

				// Set this to the delta weight
				previousDeltaWeights[layerIndex - 1] = deltaWeight;
			}
		}

		return deltaWeight;
	}

	bool SimpleGradientDescent::learningHasStopped()
	{
		return false;
	}
}
