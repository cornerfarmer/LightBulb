// Includes
#include "Learning/Supervised/GradientDescentLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"
#include "GradientCalculation/AbstractGradientCalculation.hpp"
#include "GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "GradientCalculation/Backpropagation.hpp"

namespace LightBulb
{
	GradientDescentLearningRule::GradientDescentLearningRule(GradientDescentLearningRuleOptions& options_)
		: AbstractSupervisedLearningRule(new GradientDescentLearningRuleOptions(options_))
	{
		initialize(static_cast<GradientDescentLearningRuleOptions*>(options.get()));
	}

	GradientDescentLearningRule::GradientDescentLearningRule(GradientDescentLearningRuleOptions* options_)
		: AbstractSupervisedLearningRule(options_)
	{
		initialize(options_);
	}

	GradientDescentLearningRule::GradientDescentLearningRule()
		: AbstractSupervisedLearningRule(new GradientDescentLearningRuleOptions())
	{

	}

	void GradientDescentLearningRule::initialize(GradientDescentLearningRuleOptions* options)
	{
		if (!getOptions()->gradientDescentAlgorithm)
			gradientDescentAlgorithm.reset(new SimpleGradientDescent());
		else
			gradientDescentAlgorithm.reset(getOptions()->gradientDescentAlgorithm);
		options->gradientDescentAlgorithm = nullptr;

		if (!getOptions()->gradientCalculation)
			gradientCalculation.reset(new Backpropagation());
		else
			gradientCalculation.reset(getOptions()->gradientCalculation);
		options->gradientCalculation = nullptr;
	}

	std::string GradientDescentLearningRule::getName()
	{
		return "GradientDescent";
	}


	void GradientDescentLearningRule::calculateDeltaWeight(const AbstractTeachingLesson& lesson, int lessonIndex, const ErrorMap_t& errormap)
	{
		gradientCalculation->calcGradient(getCurrentNetworkTopology(), errormap);
	}


	void GradientDescentLearningRule::adjustWeights(int layerIndex)
	{
		Eigen::MatrixXd newWeights = getCurrentNetworkTopology().getAfferentWeightsPerLayer(layerIndex) + gradientDescentAlgorithm->calcDeltaWeight(getCurrentNetworkTopology(), layerIndex, gradientCalculation->getGradient().at(layerIndex - 1));
		getCurrentNetworkTopology().setAfferentWeightsPerLayer(layerIndex, newWeights);
	}

	std::string GradientDescentLearningRule::printDebugOutput()
	{
		return gradientDescentAlgorithm->printDebugOutput();
	}

	bool GradientDescentLearningRule::learningHasStopped()
	{
		return gradientDescentAlgorithm->learningHasStopped();
	}

	const GradientDescentLearningRuleOptions* GradientDescentLearningRule::getOptions() const
	{
		return static_cast<GradientDescentLearningRuleOptions*>(options.get());
	}

	void GradientDescentLearningRule::clearGradient()
	{
		gradientCalculation->initGradient(getCurrentNetworkTopology());
	}

	void GradientDescentLearningRule::initializeTry()
	{
		// If we can change the weights before learning
		if (getOptions()->changeWeightsBeforeLearning)
		{
			// Randomize all weights
			getCurrentNetworkTopology().randomizeWeights(*randomGenerator.get(), getOptions()->minRandomWeightValue, getOptions()->maxRandomWeightValue);
			getCurrentNetworkTopology().randomizeWeights(*randomGenerator.get(), getOptions()->minRandomWeightValue, getOptions()->maxRandomWeightValue);
		}

		// If used, initialize the learning rate helper
		if (!gradientDescentAlgorithm->isInitialized())
			gradientDescentAlgorithm->initialize(getCurrentNetworkTopology());

	}
}