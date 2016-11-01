// Includes
#include "Learning/Supervised/GradientDescentAlgorithms/ResilientLearningRate.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	ResilientLearningRate::ResilientLearningRate(ResilientLearningRateOptions& options_)
		:AbstractGradientDescentAlgorithm(new ResilientLearningRateOptions(options_))
	{

	}

	ResilientLearningRate::ResilientLearningRate()
		: AbstractGradientDescentAlgorithm(new ResilientLearningRateOptions())
	{
	}

	ResilientLearningRate::ResilientLearningRate(ResilientLearningRate&& other) noexcept
		: ResilientLearningRate()
	{
		swap(*this, other);
	}

	ResilientLearningRate& ResilientLearningRate::operator=(ResilientLearningRate other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(ResilientLearningRate& lhs, ResilientLearningRate& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractGradientDescentAlgorithm&>(lhs), static_cast<AbstractGradientDescentAlgorithm&>(rhs));
		swap(lhs.previousLearningRates, rhs.previousLearningRates);
	}

	ResilientLearningRateOptions& ResilientLearningRate::getOptions()
	{
		return static_cast<ResilientLearningRateOptions&>(*options.get());
	}

	void ResilientLearningRate::initializeAlgorithm(const AbstractNetworkTopology& networkTopology)
	{
		// Make sure the previous learning rates map is empty
		previousLearningRates = networkTopology.getAllWeights();
		for (int i = 0; i < previousLearningRates.size(); i++)
		{
			previousLearningRates[i].setConstant(getOptions().learningRateStart);
		}
	}

	AbstractCloneable* ResilientLearningRate::clone() const
	{
		return new ResilientLearningRate(*this);
	}

	Eigen::MatrixXd ResilientLearningRate::calcDeltaWeight(const AbstractNetworkTopology& networkTopology, int layerIndex, const Eigen::MatrixXd& gradients)
	{
		for (int i = 0; i < gradients.rows(); i++)
		{
			for (int j = 0; j < gradients.cols(); j++)
			{
				if (gradients(i, j) != 0)
				{
					// If the sign of the gradient equals the sign of the last learning rate
					if (previousLearningRates[layerIndex - 1](i, j) * gradients(i, j) < 0)
						previousLearningRates[layerIndex - 1](i, j) *= getOptions().learningRateGrowFac; // Increase the new learning rate
					else if (previousLearningRates[layerIndex - 1](i, j) * gradients(i, j) > 0)
						previousLearningRates[layerIndex - 1](i, j) *= getOptions().learningRateShrinkFac;	 // Decrease the new learning rate

					// Make sure the new learningRate is between learningRateMin and learningRateMax
					previousLearningRates[layerIndex - 1](i, j) = std::max(getOptions().learningRateMin, std::min(getOptions().learningRateMax, std::abs(previousLearningRates[layerIndex - 1](i, j))));

					// Set the sign of the learningRate to the sign of the gradient
					previousLearningRates[layerIndex - 1](i, j) *= (gradients(i, j) < 0 ? 1 : -1);
				}
				else
					previousLearningRates[layerIndex - 1](i, j) = 0;
			}
		}

		return previousLearningRates[layerIndex - 1];
	}

	std::string ResilientLearningRate::printDebugOutput()
	{
		// Calculate the absolute sum of all learningRates
		double totalLearningRate = 0;
		for (auto previousLearningRate = previousLearningRates.begin(); previousLearningRate != previousLearningRates.end(); previousLearningRate++)
			totalLearningRate += previousLearningRate->cwiseAbs().sum();
		// Print the totalLearningRate
		return "totalLR :" + std::to_string(totalLearningRate) + " ";
	}

	bool ResilientLearningRate::learningHasStopped()
	{
		// If the previousLearningRates map is not empty (so we have done at least one iteration)
		if (!previousLearningRates.empty())
		{
			bool learningHasStopped = true;
			// If there is any learningRate, which can still change the totalError dont stop the learning process
			double totalLearningRate = 0;
			for (auto previousLearningRate = previousLearningRates.begin(); previousLearningRate != previousLearningRates.end(); previousLearningRate++)
			{
				// If the learning rate is in the allowed range, continue learning
				if (abs(previousLearningRate->maxCoeff()) > getOptions().learningRateMin && abs(previousLearningRate->minCoeff()) < getOptions().learningRateMax)
					learningHasStopped = false;

				totalLearningRate += previousLearningRate->cwiseAbs().sum();
			}

			// If the totalLearningRate is below the minium stop the learning process
			if (totalLearningRate < getOptions().minLearningRate)
				learningHasStopped = true;

			return learningHasStopped;
		}
		else
			return false;
	}
}

