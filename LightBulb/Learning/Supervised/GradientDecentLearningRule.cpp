// Includes
#include "Learning/Supervised/GradientDecentLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "GradientDecentAlgorithms/AbstractGradientDecentAlgorithm.hpp"
#include "GradientCalculation/AbstractGradientCalculation.hpp"
#include "GradientDecentAlgorithms/SimpleGradientDecent.hpp"
#include "GradientCalculation/Backpropagation.hpp"

GradientDecentLearningRule::GradientDecentLearningRule(GradientDecentLearningRuleOptions& options_)
	: AbstractSupervisedLearningRule(new GradientDecentLearningRuleOptions(options_))
{
	initialize();
}

GradientDecentLearningRule::GradientDecentLearningRule(GradientDecentLearningRuleOptions* options_)
	: AbstractSupervisedLearningRule(options_)
{
	initialize();
}


void GradientDecentLearningRule::initialize()
{
	if (!getOptions()->gradientDecentAlgorithm)
		getOptions()->gradientDecentAlgorithm = new SimpleGradientDecent();

	if (!getOptions()->gradientCalculation)
		getOptions()->gradientCalculation = new Backpropagation();
}

std::string GradientDecentLearningRule::getName()
{
	return "GradientDecent";
}


std::vector<Eigen::MatrixXd> GradientDecentLearningRule::calculateDeltaWeight(AbstractTeachingLesson& lesson, int lessonIndex, ErrorMap_t* errormap)
{
	std::vector<Eigen::MatrixXd> gradient(getCurrentNetworkTopology()->getLayerCount() - 1);
	getOptions()->gradientCalculation->calcGradient(getCurrentNetworkTopology(), errormap, gradient);
	for (int i = 0; i < gradient.size(); i++)
		gradient[i] *= -1;

	return gradient;
}


void GradientDecentLearningRule::adjustWeights(int layerIndex, Eigen::MatrixXd gradients)
{
	Eigen::MatrixXd newWeights = getCurrentNetworkTopology()->getAfferentWeightsPerLayer(layerIndex) + getOptions()->gradientDecentAlgorithm->calcDeltaWeight(layerIndex, gradients);
	getCurrentNetworkTopology()->setAfferentWeightsPerLayer(layerIndex, newWeights);
}

std::string GradientDecentLearningRule::printDebugOutput()
{
	return getOptions()->gradientDecentAlgorithm->printDebugOutput();
}

bool GradientDecentLearningRule::learningHasStopped()
{
	return getOptions()->gradientDecentAlgorithm->learningHasStopped();
}

GradientDecentLearningRuleOptions* GradientDecentLearningRule::getOptions()
{
	return static_cast<GradientDecentLearningRuleOptions*>(options.get());
}

void GradientDecentLearningRule::initializeTry()
{
	// If we can change the weights before learning
	if (getOptions()->changeWeightsBeforeLearning)
	{
		// Randomize all weights
		getCurrentNetworkTopology()->randomizeWeights(randomGenerator.get(), getOptions()->minRandomWeightValue, getOptions()->maxRandomWeightValue);
		getCurrentNetworkTopology()->randomizeWeights(randomGenerator.get(), getOptions()->minRandomWeightValue, getOptions()->maxRandomWeightValue);
	}

	// If used, initialize the learning rate helper
	getOptions()->gradientDecentAlgorithm->initialize(*getOptions()->neuralNetwork);

}