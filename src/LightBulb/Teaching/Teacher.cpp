// Includes
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/Teaching/Teacher.hpp"
#include "LightBulb/ActivationOrder/AbstractActivationOrder.hpp"
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	void Teacher::addTestingLesson(AbstractTeachingLesson* newTestingLesson)
	{
		// Add the newTeachingLesson to the list
		testingLessons.push_back(std::unique_ptr<AbstractTeachingLesson>(newTestingLesson));

	}

	Teacher::Teacher(double weightDecayFac_)
	{
		weightDecayFac = weightDecayFac_;
	}

	void Teacher::addTeachingLesson(AbstractTeachingLesson* newTeachingLesson)
	{
		// Add the newTeachingLesson to the list
		teachingLessons.push_back(std::unique_ptr<AbstractTeachingLesson>(newTeachingLesson));
	}

	const std::vector<std::unique_ptr<AbstractTeachingLesson>>& Teacher::getTeachingLessons() const
	{
		return teachingLessons;
	}

	const std::vector<std::unique_ptr<AbstractTeachingLesson>>& Teacher::getTestingLessons() const
	{
		return testingLessons;
	}


	double Teacher::getTotalError(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder) const
	{
		return getTeachingError(neuralNetwork, activationOrder) + getWeightDecayError(neuralNetwork);
	}

	double Teacher::getTeachingError(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder) const
	{
		double totalError = 0;

		// Add every specific error of the teachingLessons to the total error
		for (auto teachingLesson = teachingLessons.begin(); teachingLesson != teachingLessons.end(); teachingLesson++)
		{
			totalError += (*teachingLesson)->getSpecificError(neuralNetwork, activationOrder);
		}

		// Add every specific error of the testingLessons to the total error
		for (auto testinggLesson = testingLessons.begin(); testinggLesson != testingLessons.end(); testinggLesson++)
		{
			totalError += (*testinggLesson)->getSpecificError(neuralNetwork, activationOrder);
		}

		return totalError;
	}


	double Teacher::getWeightDecayError(AbstractNeuralNetwork& neuralNetwork) const
	{
		double weightDecayError = 0;
		if (weightDecayFac > 0)
		{
			std::vector<Matrix>& weights = neuralNetwork.getNetworkTopology().getAllWeights();
			for (auto weightsPerLayer = weights.begin(); weightsPerLayer != weights.end(); weightsPerLayer++)
			{
				weightDecayError += 0.5 * weightsPerLayer->getEigenValue().squaredNorm();
			}
		}
		return weightDecayFac * weightDecayError;
	}

	void Teacher::clearLessons()
	{
		teachingLessons.clear();
		testingLessons.clear();
	}
}
