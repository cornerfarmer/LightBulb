// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Evolution/CoevolutionLearningRule.hpp"
#include "LightBulb/Logging/AbstractLogger.hpp"
#include "LightBulb/Learning/LearningState.hpp"

// Library includes

namespace LightBulb
{
	AbstractLearningResult* CoevolutionLearningRule::getLearningResult()
	{
		return getOptions().learningRule1->getLearningResult();
	}

	CoevolutionLearningRule::CoevolutionLearningRule(CoevolutionLearningRuleOptions& options_)
		: AbstractEvolutionLearningRule(new CoevolutionLearningRuleOptions(options_))
	{
		exitConditionReached = false;
	}

	CoevolutionLearningRule::CoevolutionLearningRule(CoevolutionLearningRuleOptions* options_)
		: AbstractEvolutionLearningRule(options_)
	{
		exitConditionReached = false;
	}

	CoevolutionLearningRule::CoevolutionLearningRule()
		: AbstractEvolutionLearningRule(new CoevolutionLearningRuleOptions())
	{
		exitConditionReached = false;
	}

	std::string CoevolutionLearningRule::getName()
	{
		return "CoevolutionLearningRule";
	}

	std::vector<std::string> CoevolutionLearningRule::getDataSetLabels() const
	{
		std::vector<std::string> labels1 = getOptions().learningRule1->getDataSetLabels();
		std::vector<std::string> labels2 = getOptions().learningRule2->getDataSetLabels();
		labels1.insert(labels1.end(), labels2.begin(), labels2.end());
		return labels1;
	}

	AbstractEvolutionLearningRule& CoevolutionLearningRule::getFirstLearningRule()
	{
		return *getOptions().learningRule1;
	}


	AbstractEvolutionLearningRule& CoevolutionLearningRule::getSecondLearningRule()
	{
		return *getOptions().learningRule2;
	}


	void CoevolutionLearningRule::initializeStartLearningAlgoritm()
	{
		exitConditionReached = false;
		getOptions().learningRule1->learningState = learningState;
		getOptions().learningRule2->learningState = learningState;
		getOptions().learningRule1->setLogger(*options->logger);
		getOptions().learningRule2->setLogger(*options->logger);
		getOptions().learningRule1->randomGenerator = randomGenerator;
		getOptions().learningRule2->randomGenerator = randomGenerator;
		getOptions().learningRule1->zigguratGenerator = zigguratGenerator;
		getOptions().learningRule2->zigguratGenerator = zigguratGenerator;
		getOptions().learningRule1->setHelperToUsedObjects();
		getOptions().learningRule2->setHelperToUsedObjects();
		getOptions().learningRule2->options->dataSetsPrefix = "Parasite - ";
	}

	const CoevolutionLearningRuleOptions& CoevolutionLearningRule::getOptions() const
	{
		return static_cast<CoevolutionLearningRuleOptions&>(*options.get());
	}

	void CoevolutionLearningRule::doIteration()
	{
		log("lr1: ", LL_MEDIUM);
		getOptions().learningRule1->doIteration();
		learningState->iterations--;
		if (getOptions().learningRule1->hasLearningSucceeded()) {
			exitConditionReached = true;
			return;
		}

		log("lr2: ", LL_MEDIUM);
		getOptions().learningRule2->doIteration();
		learningState->iterations--;
		if (getOptions().learningRule2->hasLearningSucceeded()) {
			exitConditionReached = true;
			return;
		}
	}

	void CoevolutionLearningRule::initializeTry()
	{
		getOptions().learningRule1->initializeTry();
		getOptions().learningRule2->initializeTry();
	}

	bool CoevolutionLearningRule::hasLearningSucceeded()
	{
		return exitConditionReached;
	}
}