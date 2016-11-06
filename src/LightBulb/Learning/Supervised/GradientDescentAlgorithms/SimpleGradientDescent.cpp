// Includes
#include "Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

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
				previousDeltaWeights[i].setZero();
			}
		}
	}

	AbstractCloneable* SimpleGradientDescent::clone() const
	{
		return new SimpleGradientDescent(*this);
	}

	Eigen::MatrixXd SimpleGradientDescent::calcDeltaWeight(const AbstractNetworkTopology& networkTopology, int layerIndex, const Eigen::MatrixXd& gradients)
	{
		Eigen::MatrixXd deltaWeight;

		// Calc the delta weight
		deltaWeight = -getOptions().learningRate * gradients;

		// Substract the weightDecay term
		deltaWeight -= getOptions().weightDecayFac * networkTopology.getAfferentWeightsPerLayer(layerIndex);

		if (getOptions().momentum > 0) {
			// Add the momentum term
			deltaWeight += getOptions().momentum * previousDeltaWeights[layerIndex - 1];

			// Set this to the delta weight
			previousDeltaWeights[layerIndex - 1] = deltaWeight;
		}

		return deltaWeight;
	}

	bool SimpleGradientDescent::learningHasStopped()
	{
		return false;
	}
}
