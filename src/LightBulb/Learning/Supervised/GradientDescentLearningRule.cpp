// Includes
#include "LightBulb/Learning/Supervised/GradientDescentLearningRule.hpp"
#include "LightBulb/Teaching/Teacher.hpp"
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"
#include "LightBulb/Learning/Supervised/GradientCalculation/AbstractGradientCalculation.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "LightBulb/Learning/Supervised/GradientCalculation/Backpropagation.hpp"

namespace LightBulb
{
	GradientDescentLearningRuleOptions::~GradientDescentLearningRuleOptions()
	{
		delete(gradientCalculation);
		delete(gradientDescentAlgorithm);
	}

	GradientDescentLearningRuleOptions::GradientDescentLearningRuleOptions(const GradientDescentLearningRuleOptions& other)
		:AbstractSupervisedLearningRuleOptions(other)
	{
		if (other.gradientCalculation)
			gradientCalculation = dynamic_cast<AbstractGradientCalculation*>(other.gradientCalculation->clone());
		else
			gradientCalculation = nullptr;

		if (other.gradientDescentAlgorithm)
			gradientDescentAlgorithm = dynamic_cast<AbstractGradientDescentAlgorithm*>(other.gradientDescentAlgorithm->clone());
		else
			gradientDescentAlgorithm = nullptr;
	}

	GradientDescentLearningRuleOptions::GradientDescentLearningRuleOptions(GradientDescentLearningRuleOptions&& other) noexcept
		: GradientDescentLearningRuleOptions()
	{
		swap(*this, other);
	}

	GradientDescentLearningRuleOptions& GradientDescentLearningRuleOptions::operator=(GradientDescentLearningRuleOptions other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(GradientDescentLearningRuleOptions& lhs, GradientDescentLearningRuleOptions& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractSupervisedLearningRuleOptions&>(lhs), static_cast<AbstractSupervisedLearningRuleOptions&>(rhs));
		swap(lhs.gradientCalculation, rhs.gradientCalculation);
		swap(lhs.gradientDescentAlgorithm, rhs.gradientDescentAlgorithm);
	}

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

		gradientDescentAlgorithm->setCalculatorType(getOptions()->calculatorType);
		gradientCalculation->setCalculatorType(getOptions()->calculatorType);
		getOptions()->neuralNetwork->getNetworkTopology().setCalculatorType(getOptions()->calculatorType);
	}

	std::string GradientDescentLearningRule::getName()
	{
		return "GradientDescent";
	}


	void GradientDescentLearningRule::calculateDeltaWeight(const AbstractTeachingLesson& lesson, int lessonIndex, const Vector& errorVector)
	{
		gradientCalculation->calcGradient(getCurrentNetworkTopology(), errorVector, &lesson.getTeachingPatternVector());
	}


	void GradientDescentLearningRule::adjustWeights(int layerIndex)
	{
		gradientDescentAlgorithm->adjustWeights(getCurrentNetworkTopology(), getCurrentNetworkTopology().getAllWeights()[layerIndex - 1], layerIndex, gradientCalculation->getGradient().at(layerIndex - 1));
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
