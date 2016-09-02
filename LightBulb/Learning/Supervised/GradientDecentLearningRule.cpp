// Includes
#include "Learning/Supervised/GradientDecentLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
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

GradientDecentLearningRule::GradientDecentLearningRule()
	:AbstractSupervisedLearningRule(new GradientDecentLearningRuleOptions())
{

}

void GradientDecentLearningRule::initialize()
{
	if (!getOptions()->gradientDecentAlgorithm)
		gradientDecentAlgorithm.reset(new SimpleGradientDecent());
	else
		gradientDecentAlgorithm.reset(getOptions()->gradientDecentAlgorithm);
	getOptions()->gradientDecentAlgorithm = NULL;

	if (!getOptions()->gradientCalculation)
		gradientCalculation.reset(new Backpropagation());
	else
		gradientCalculation.reset(getOptions()->gradientCalculation);
	getOptions()->gradientCalculation = NULL;
}

std::string GradientDecentLearningRule::getName()
{
	return "GradientDecent";
}


std::vector<Eigen::MatrixXd> GradientDecentLearningRule::calculateDeltaWeight(AbstractTeachingLesson& lesson, int lessonIndex, ErrorMap_t* errormap)
{
	std::vector<Eigen::MatrixXd> gradient(getCurrentNetworkTopology()->getLayerCount() - 1);
	gradientCalculation->calcGradient(getCurrentNetworkTopology(), errormap, gradient);
	for (int i = 0; i < gradient.size(); i++)
		gradient[i] *= -1;

	return gradient;
}


void GradientDecentLearningRule::adjustWeights(int layerIndex, Eigen::MatrixXd gradients)
{
	Eigen::MatrixXd newWeights = getCurrentNetworkTopology()->getAfferentWeightsPerLayer(layerIndex) + gradientDecentAlgorithm->calcDeltaWeight(getCurrentNetworkTopology(), layerIndex, gradients);
	getCurrentNetworkTopology()->setAfferentWeightsPerLayer(layerIndex, newWeights);
}

std::string GradientDecentLearningRule::printDebugOutput()
{
	return gradientDecentAlgorithm->printDebugOutput();
}

bool GradientDecentLearningRule::learningHasStopped()
{
	return gradientDecentAlgorithm->learningHasStopped();
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
	if (!gradientDecentAlgorithm->isInitialized())
		gradientDecentAlgorithm->initialize(getCurrentNetworkTopology());

}