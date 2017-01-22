// Includes
#include "LightBulb/Learning/Evolution/EvolutionLearningRule.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp"
#include "LightBulb/Learning/Evolution/AbstractCreationCommand.hpp"
#include "LightBulb/Learning/Evolution/AbstractSelectionCommand.hpp"
#include "LightBulb/Learning/Evolution/AbstractFitnessFunction.hpp"
#include "LightBulb/Learning/Evolution/AbstractMutationCommand.hpp"
#include "LightBulb/Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "LightBulb/Learning/Evolution/AbstractExitCondition.hpp"
#include "LightBulb/Learning/Evolution/AbstractReuseCommand.hpp"
#include "LightBulb/Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningResult.hpp"
// Library includes
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

namespace LightBulb
{
	AbstractLearningResult* EvolutionLearningRule::getLearningResult()
	{
		EvolutionLearningResult* learningResult = new EvolutionLearningResult();
		fillDefaultResults(*learningResult);
		const Highscore& highscore = getOptions().environment->getHighscoreList();
		learningResult->bestFitness = highscore.front().first;
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			learningResult->bestIndividuals.push_back(std::unique_ptr<AbstractIndividual>(entry->second));
		}
		getOptions().environment->clearPopulation();

		return learningResult;
	}

	EvolutionLearningRule::EvolutionLearningRule(EvolutionLearningRuleOptions& options_)
		: AbstractEvolutionLearningRule(new EvolutionLearningRuleOptions(options_))
	{
		EvolutionLearningRule::setHelperToUsedObjects();
		exitConditionReached = false;
	}

	EvolutionLearningRule::EvolutionLearningRule(EvolutionLearningRuleOptions* options_)
		: AbstractEvolutionLearningRule(options_)
	{
		EvolutionLearningRule::setHelperToUsedObjects();
		exitConditionReached = false;
	}

	EvolutionLearningRule::EvolutionLearningRule()
		: AbstractEvolutionLearningRule(new EvolutionLearningRuleOptions())
	{

	}

	void EvolutionLearningRule::setHelperToUsedObjects()
	{
		getOptions().environment->setLogger(*options->logger);
		getOptions().environment->setLearningState(*learningState.get());
		getOptions().environment->setRandomGenerator(*randomGenerator.get());
		getOptions().environment->setCalculatorType(options->calculatorType);

		for (auto reuseCommand = getOptions().reuseCommands.begin(); reuseCommand != getOptions().reuseCommands.end(); reuseCommand++)
		{
			(*reuseCommand)->setLogger(*options->logger);
			(*reuseCommand)->setRandomGenerator(*randomGenerator.get());
			(*reuseCommand)->setCalculatorType(options->calculatorType);
		}

		for (auto mutationCommand = getOptions().mutationsCommands.begin(); mutationCommand != getOptions().mutationsCommands.end(); mutationCommand++)
		{
			(*mutationCommand)->setLogger(*options->logger);
			(*mutationCommand)->setRandomGenerator(*randomGenerator.get());
			(*mutationCommand)->setZigguratGenerator(*zigguratGenerator.get());
			(*mutationCommand)->setCalculatorType(options->calculatorType);
		}

		for (auto recombinationCommand = getOptions().recombinationCommands.begin(); recombinationCommand != getOptions().recombinationCommands.end(); recombinationCommand++)
		{
			(*recombinationCommand)->setLogger(*options->logger);
			(*recombinationCommand)->setRandomGenerator(*randomGenerator.get());
			(*recombinationCommand)->setCalculatorType(options->calculatorType);
		}

		for (auto fitnessFunction = getOptions().fitnessFunctions.begin(); fitnessFunction != getOptions().fitnessFunctions.end(); fitnessFunction++)
		{
			(*fitnessFunction)->setLogger(*options->logger);
			(*fitnessFunction)->setCalculatorType(options->calculatorType);
		}

		for (auto creationCommand = getOptions().creationCommands.begin(); creationCommand != getOptions().creationCommands.end(); creationCommand++)
		{
			(*creationCommand)->setLogger(*options->logger);
			(*creationCommand)->setRandomGenerator(*randomGenerator.get());
			(*creationCommand)->setCalculatorType(options->calculatorType);
		}

		for (auto exitCondition = getOptions().exitConditions.begin(); exitCondition != getOptions().exitConditions.end(); exitCondition++)
		{
			(*exitCondition)->setLogger(*options->logger);
		}

		for (auto selectionCommand = getOptions().selectionCommands.begin(); selectionCommand != getOptions().selectionCommands.end(); selectionCommand++)
		{
			(*selectionCommand)->setLogger(*options->logger);
			(*selectionCommand)->setRandomGenerator(*randomGenerator.get());
			(*selectionCommand)->setCalculatorType(options->calculatorType);
		}
	}

	bool EvolutionLearningRule::hasLearningSucceeded()
	{
		return exitConditionReached;
	}

	void EvolutionLearningRule::initializeTry()
	{
		// Reset all
		getOptions().environment->clearPopulation();
		getOptions().environment->initializeForLearning();
	}

	std::string EvolutionLearningRule::getName()
	{
		return "EvolutionLearningRule";
	}

	std::vector<std::string> EvolutionLearningRule::getDataSetLabels() const
	{
		std::vector<std::string> labels = AbstractLearningRule::getDataSetLabels();
		labels.push_back(getOptions().dataSetsPrefix + DATA_SET_FITNESS);
		labels.push_back(getOptions().dataSetsPrefix + DATA_AVG_NEURON_COUNT);
		labels.push_back(getOptions().dataSetsPrefix + DATA_BEST_NEURON_COUNT);
		std::vector<std::string> environmentLabels = getOptions().environment->getDataSetLabels();
		labels.insert(labels.end(), environmentLabels.begin(), environmentLabels.end());
		return labels;
	}

	void EvolutionLearningRule::setLogger(AbstractLogger& logger)
	{
		AbstractLearningRule::setLogger(logger);
		setHelperToUsedObjects();
	}

	void EvolutionLearningRule::doIteration()
	{
		if (!options->disabledDataSets[getOptions().dataSetsPrefix + DATA_SET_FITNESS] && getOptions().environment->getPopulationSize() > 0)
			learningState->addData(getOptions().dataSetsPrefix + DATA_SET_FITNESS, getOptions().environment->getHighscoreList().front().first);


		log("------------- Generation " + std::to_string(learningState->iterations) + " -----------------", LL_LOW);

		if (getOptions().environment->getPopulationSize() > 0) {
			// Extract all current individuals ordered by their fitness
			const Highscore& highscore = getOptions().environment->getHighscoreList();
			// This vector will contain all individuals for the next generation
			std::vector<AbstractIndividual*> newIndividualVector;
			std::map<AbstractIndividual*, int> operationCounter;

			// 5. Step: Reuse some of the individuals directly for the next generation
			for (auto reuseCommand = getOptions().reuseCommands.begin(); reuseCommand != getOptions().reuseCommands.end(); reuseCommand++)
			{
				(*reuseCommand)->select(highscore, operationCounter);
			}

			// 6. Step: Mutate some of the individuals and use them for the next getOptions()
			for (auto mutationCommand = getOptions().mutationsCommands.begin(); mutationCommand != getOptions().mutationsCommands.end(); mutationCommand++)
			{
				(*mutationCommand)->select(highscore, operationCounter);
			}

			// 7. Step: Combine some pairs of individuals and use the created ones for the next generation
			for (auto recombinationCommand = getOptions().recombinationCommands.begin(); recombinationCommand != getOptions().recombinationCommands.end(); recombinationCommand++)
			{
				(*recombinationCommand)->select(highscore, operationCounter);
			}

			for (auto individual = getOptions().environment->getIndividuals().begin(); individual != getOptions().environment->getIndividuals().end(); individual++)
			{
				if (operationCounter[*individual] == 0)
					notUsedIndividuals.push_back(*individual);
			}

			// 7. Step: Combine some pairs of individuals and use the created ones for the next generation
			for (auto recombinationCommand = getOptions().recombinationCommands.begin(); recombinationCommand != getOptions().recombinationCommands.end(); recombinationCommand++)
			{
				(*recombinationCommand)->execute(newIndividualVector, operationCounter, notUsedIndividuals);
			}

			// 6. Step: Mutate some of the individuals and use them for the next generation
			for (auto mutationCommand = getOptions().mutationsCommands.begin(); mutationCommand != getOptions().mutationsCommands.end(); mutationCommand++)
			{
				(*mutationCommand)->execute(newIndividualVector, operationCounter, notUsedIndividuals);
			}

			// 5. Step: Reuse some of the individuals directly for the next generation
			for (auto reuseCommand = getOptions().reuseCommands.begin(); reuseCommand != getOptions().reuseCommands.end(); reuseCommand++)
			{
				(*reuseCommand)->execute(newIndividualVector, operationCounter, notUsedIndividuals);
			}

			// Replace all individuals from the last generation with the one from the next generation
			getOptions().environment->setIndividuals(newIndividualVector);
		}


		// 1. Step: Create new individuals
		for (auto creationCommand = getOptions().creationCommands.begin(); creationCommand != getOptions().creationCommands.end(); creationCommand++)
		{
			(*creationCommand)->execute(*getOptions().environment, notUsedIndividuals);
		}

		// Reset the environment for the next generation
		getOptions().environment->reset();

		// 2. Step: Execute the simulation and try to rate the individuals
		getOptions().environment->doSimulationStep();
		getOptions().environment->refreshHighscore();

		// Extract all current individuals ordered by their fitness
		Highscore& highscore = getOptions().environment->getHighscoreList();

		// {2,3}.5. Step: Modify the calculated scores
		for (auto fitnessFunction = getOptions().fitnessFunctions.begin(); fitnessFunction != getOptions().fitnessFunctions.end(); fitnessFunction++)
		{
			(*fitnessFunction)->execute(highscore);
		}

		if (!options->disabledDataSets[getOptions().dataSetsPrefix + DATA_AVG_NEURON_COUNT])
		{
			int totalNeuronCount = 0;
			for (int i = 0; i < highscore.size(); i++)
			{
				totalNeuronCount += highscore[i].second->getNeuralNetwork().getNetworkTopology().getNeuronCount();
			}
			learningState->addData(getOptions().dataSetsPrefix + DATA_AVG_NEURON_COUNT, static_cast<double>(totalNeuronCount) / highscore.size());
		}

		if (!options->disabledDataSets[getOptions().dataSetsPrefix + DATA_BEST_NEURON_COUNT])
		{
			learningState->addData(getOptions().dataSetsPrefix + DATA_BEST_NEURON_COUNT, highscore.front().second->getNeuralNetwork().getNetworkTopology().getNeuronCount());
		}

		throwEvent(EVT_EL_EVOLUTIONSTEP, *this);

		bool exit = false;
		// 3.Step: Go through all exit conditions
		for (auto exitCondition = getOptions().exitConditions.begin(); exitCondition != getOptions().exitConditions.end(); exitCondition++)
		{
			// Evaluate them and connect them with an OR
			exit |= (*exitCondition)->evaluate(highscore, *this);
		}
		// If at least one condition was true => stop this try
		if (exit) {
			exitConditionReached = true;
			log("At least one condition is true => exit", LL_HIGH);
			return;
		}

		// 4. Step: Select the relevant individuals (Other individuals will be deleted)
		for (auto selectionCommand = getOptions().selectionCommands.begin(); selectionCommand != getOptions().selectionCommands.end(); selectionCommand++)
		{
			(*selectionCommand)->execute(highscore, getOptions().environment->getIndividuals(), notUsedIndividuals);
		}

		// Continue with the next generation
		learningState->iterations++;
	}

	const EvolutionLearningRuleOptions& EvolutionLearningRule::getOptions() const
	{
		return static_cast<EvolutionLearningRuleOptions&>(*options.get());
	}

	void EvolutionLearningRule::doCalculationAfterLearningProcess()
	{
		if (!options->disabledDataSets[getOptions().dataSetsPrefix + DATA_SET_FITNESS])
			learningState->addData(getOptions().dataSetsPrefix + DATA_SET_FITNESS, getOptions().environment->getHighscoreList().front().first);
	}

	EvolutionLearningRuleOptions::~EvolutionLearningRuleOptions()
	{
		for (auto exitCondition = exitConditions.begin(); exitCondition != exitConditions.end(); exitCondition++)
		{
			delete(*exitCondition);
		}
		for (auto creationCommand = creationCommands.begin(); creationCommand != creationCommands.end(); creationCommand++)
		{
			delete(*creationCommand);
		}
		for (auto selectionCommand = selectionCommands.begin(); selectionCommand != selectionCommands.end(); selectionCommand++)
		{
			delete(*selectionCommand);
		}
		for (auto fitnessFunction = fitnessFunctions.begin(); fitnessFunction != fitnessFunctions.end(); fitnessFunction++)
		{
			delete(*fitnessFunction);
		}
		for (auto mutationsCommand = mutationsCommands.begin(); mutationsCommand != mutationsCommands.end(); mutationsCommand++)
		{
			delete(*mutationsCommand);
		}
		for (auto recombinationCommand = recombinationCommands.begin(); recombinationCommand != recombinationCommands.end(); recombinationCommand++)
		{
			delete(*recombinationCommand);
		}
		for (auto reuseCommand = reuseCommands.begin(); reuseCommand != reuseCommands.end(); reuseCommand++)
		{
			delete(*reuseCommand);
		}
	}

	EvolutionLearningRuleOptions::EvolutionLearningRuleOptions(const EvolutionLearningRuleOptions& other)
		:AbstractEvolutionLearningRuleOptions(other)
	{
		for (auto exitCondition = other.exitConditions.begin(); exitCondition != other.exitConditions.end(); exitCondition++)
		{
			exitConditions.push_back(dynamic_cast<AbstractExitCondition*>((*exitCondition)->clone()));
		}
		for (auto creationCommand = other.creationCommands.begin(); creationCommand != other.creationCommands.end(); creationCommand++)
		{
			creationCommands.push_back(dynamic_cast<AbstractCreationCommand*>((*creationCommand)->clone()));
		}
		for (auto selectionCommand = other.selectionCommands.begin(); selectionCommand != other.selectionCommands.end(); selectionCommand++)
		{
			selectionCommands.push_back(dynamic_cast<AbstractSelectionCommand*>((*selectionCommand)->clone()));
		}
		for (auto fitnessFunction = other.fitnessFunctions.begin(); fitnessFunction != other.fitnessFunctions.end(); fitnessFunction++)
		{
			fitnessFunctions.push_back(dynamic_cast<AbstractFitnessFunction*>((*fitnessFunction)->clone()));
		}
		for (auto mutationsCommand = other.mutationsCommands.begin(); mutationsCommand != other.mutationsCommands.end(); mutationsCommand++)
		{
			mutationsCommands.push_back(dynamic_cast<AbstractMutationCommand*>((*mutationsCommand)->clone()));
		}
		for (auto recombinationCommand = other.recombinationCommands.begin(); recombinationCommand != other.recombinationCommands.end(); recombinationCommand++)
		{
			recombinationCommands.push_back(dynamic_cast<AbstractRecombinationCommand*>((*recombinationCommand)->clone()));
		}
		for (auto reuseCommand = other.reuseCommands.begin(); reuseCommand != other.reuseCommands.end(); reuseCommand++)
		{
			reuseCommands.push_back(dynamic_cast<AbstractReuseCommand*>((*reuseCommand)->clone()));
		}
	}

	EvolutionLearningRuleOptions::EvolutionLearningRuleOptions(EvolutionLearningRuleOptions&& other) noexcept
		:EvolutionLearningRuleOptions()
	{
		swap(*this, other);
	}

	EvolutionLearningRuleOptions& EvolutionLearningRuleOptions::operator=(EvolutionLearningRuleOptions other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(EvolutionLearningRuleOptions& lhs, EvolutionLearningRuleOptions& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractEvolutionLearningRuleOptions&>(lhs), static_cast<AbstractEvolutionLearningRuleOptions&>(rhs));
		swap(lhs.exitConditions, rhs.exitConditions);
		swap(lhs.creationCommands, rhs.creationCommands);
		swap(lhs.selectionCommands, rhs.selectionCommands);
		swap(lhs.fitnessFunctions, rhs.fitnessFunctions);
		swap(lhs.mutationsCommands, rhs.mutationsCommands);
		swap(lhs.recombinationCommands, rhs.recombinationCommands);
		swap(lhs.reuseCommands, rhs.reuseCommands);
	}
}
