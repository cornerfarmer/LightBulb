// Includes
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

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

	const std::vector<std::unique_ptr<AbstractTeachingLesson>>* Teacher::getTeachingLessons() const
	{
		return &teachingLessons;
	}

	const std::vector<std::unique_ptr<AbstractTeachingLesson>>* Teacher::getTestingLessons() const
	{
		return &testingLessons;
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
			auto weights = neuralNetwork.getNetworkTopology()->getAllWeights();
			for (auto weightsPerLayer = weights->begin(); weightsPerLayer != weights->end(); weightsPerLayer++)
			{
				weightDecayError += 0.5 * weightsPerLayer->squaredNorm();
			}
		}
		return weightDecayFac * weightDecayError;
	}

	AbstractTeacher* Teacher::unfold() const
	{
		// Create a new teacher
		AbstractTeacher* unfoldedTeacher = new Teacher();
		// Unfold all teaching lessons
		for (auto originalTeachingLesson = teachingLessons.begin(); originalTeachingLesson != teachingLessons.end(); originalTeachingLesson++)
		{
			unfoldedTeacher->addTeachingLesson((*originalTeachingLesson)->unfold());
		}

		// Unfold all testing lessons
		for (auto originalTestingLesson = testingLessons.begin(); originalTestingLesson != testingLessons.end(); originalTestingLesson++)
		{
			unfoldedTeacher->addTestingLesson((*originalTestingLesson)->unfold());
		}
		return unfoldedTeacher;
	}

	int Teacher::getMaxTimeStep() const
	{
		int maxTimeStep = 0;
		// Find the biggest timestep of all teaching lessons
		for (auto teachingLesson = teachingLessons.begin(); teachingLesson != teachingLessons.end(); teachingLesson++)
		{
			maxTimeStep = std::max(maxTimeStep, (*teachingLesson)->getMaxTimeStep());
		}
		return maxTimeStep;
	}

	void Teacher::clearLessons()
	{
		teachingLessons.clear();
		testingLessons.clear();
	}
}
