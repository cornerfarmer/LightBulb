#include "RBFNetworkBiggerExample.hpp"
//#include <Graphics/RBFNetworkStructureChart.hpp>
//#include <Graphics/NeuralNetworkResultChart.hpp>
#include <ClusterAnalysis/ROLFNeuronPlacer.hpp>
#include <Learning/RBFInterpolationLearningRule.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>
#include <Teaching/TeachingLessonLinearInput.hpp>
#include <NetworkTopology/RBFNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Teaching/Teacher.hpp>
#include <ClusterAnalysis/KMeansRBFNeuronPlacer.hpp>


AbstractLearningRule* RBFNetworkBiggerExample::createLearningRate()
{
	teacher.reset(new Teacher());
	for (int i = 0; i <= 20; i += 1)
	{
		for (int l = 0; l <= 20; l += 1)
		{
			std::vector<std::vector<double>> teachingPattern(1, std::vector<double>(2));
			NeuralNetworkIO<double>* teachingInput = new NeuralNetworkIO<double>(1);

			teachingPattern[0][0] = i;
			teachingPattern[0][1] = l;
			(*teachingInput).set(0, 0, (i > l));

			teacher->addTeachingLesson(new TeachingLessonLinearInput(teachingPattern, teachingInput));
		}
	}

	RBFInterpolationLearningRuleOptions learningRuleOptions;
	learningRuleOptions.offlineLearning = true;
	learningRuleOptions.totalErrorGoal = 2;
	learningRuleOptions.maxTotalErrorValue = 5;
	learningRuleOptions.maxTries = 1;
	learningRuleOptions.neuronPlacer = new KMeansRBFNeuronPlacer();
	learningRuleOptions.teacher = teacher.get();
	fillDefaultLearningRuleOptions(&learningRuleOptions);

	return new RBFInterpolationLearningRule(learningRuleOptions);
}

AbstractNeuralNetwork* RBFNetworkBiggerExample::createNeuralNetwork()
{
	RBFNetwork* rbfNetwork = new RBFNetwork(2, 32, 1);

	return new NeuralNetwork(rbfNetwork);
}


std::string RBFNetworkBiggerExample::getDefaultName()
{
	return "RBFNetwork bigger example";
}

std::string RBFNetworkBiggerExample::getDescription()
{
	return "Trains a rbf network to simulate the compare (bigger) function!";
}

AbstractTrainingPlan* RBFNetworkBiggerExample::getCopy()
{
	return new RBFNetworkBiggerExample();
}

int RBFNetworkBiggerExample::getRequiredInputSize()
{
	return 2;
}

int RBFNetworkBiggerExample::getRequiredOutputSize()
{
	return 1;
}

std::string RBFNetworkBiggerExample::getLearningRuleName()
{
	return RBFInterpolationLearningRule::getName();
}
