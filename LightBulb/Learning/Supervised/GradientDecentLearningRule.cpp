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

namespace LightBulb
{
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
		: AbstractSupervisedLearningRule(new GradientDecentLearningRuleOptions())
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


	void GradientDecentLearningRule::calculateDeltaWeight(AbstractTeachingLesson& lesson, int lessonIndex, ErrorMap_t* errormap)
	{
		gradientCalculation->calcGradient(getCurrentNetworkTopology(), errormap);
	}


	void GradientDecentLearningRule::adjustWeights(int layerIndex)
	{
		Eigen::MatrixXd newWeights = getCurrentNetworkTopology()->getAfferentWeightsPerLayer(layerIndex) + gradientDecentAlgorithm->calcDeltaWeight(getCurrentNetworkTopology(), layerIndex, gradientCalculation->getGradient()->at(layerIndex - 1));
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

	void GradientDecentLearningRule::clearGradient()
	{
		gradientCalculation->initGradient(getCurrentNetworkTopology());
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
}