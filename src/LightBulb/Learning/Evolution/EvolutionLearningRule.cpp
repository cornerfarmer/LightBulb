// Includes
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractCreationCommand.hpp"
#include "Learning/Evolution/AbstractSelectionCommand.hpp"
#include "Learning/Evolution/AbstractFitnessFunction.hpp"
#include "Learning/Evolution/AbstractMutationCommand.hpp"
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "Learning/Evolution/AbstractExitCondition.hpp"
#include "Learning/Evolution/AbstractReuseCommand.hpp"
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
// Library includes
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <Learning/Evolution/EvolutionLearningResult.hpp>

namespace LightBulb
{
	AbstractLearningResult* EvolutionLearningRule::getLearningResult()
	{
		EvolutionLearningResult* learningResult = new EvolutionLearningResult();
		fillDefaultResults(*learningResult);
		const Highscore& highscore = getOptions().world->getHighscoreList();
		learningResult->quality = highscore.front().first;
		learningResult->qualityLabel = "Best fitness";
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			learningResult->bestObjects.push_back(std::unique_ptr<AbstractEvolutionObject>(entry->second));
		}
		getOptions().world->clearPopulation();

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
		getOptions().world->setLogger(*options->logger);
		getOptions().world->setLearningState(*learningState.get());
		getOptions().world->setRandomGenerator(*randomGenerator.get());

		for (auto reuseCommand = getOptions().reuseCommands.begin(); reuseCommand != getOptions().reuseCommands.end(); reuseCommand++)
		{
			(*reuseCommand)->setLogger(*options->logger);
			(*reuseCommand)->setRandomGenerator(*randomGenerator.get());
		}

		for (auto mutationCommand = getOptions().mutationsCommands.begin(); mutationCommand != getOptions().mutationsCommands.end(); mutationCommand++)
		{
			(*mutationCommand)->setLogger(*options->logger);
			(*mutationCommand)->setRandomGenerator(*randomGenerator.get());
			(*mutationCommand)->setZigguratGenerator(*zigguratGenerator.get());
		}

		for (auto recombinationCommand = getOptions().recombinationCommands.begin(); recombinationCommand != getOptions().recombinationCommands.end(); recombinationCommand++)
		{
			(*recombinationCommand)->setLogger(*options->logger);
			(*recombinationCommand)->setRandomGenerator(*randomGenerator.get());
		}

		for (auto fitnessFunction = getOptions().fitnessFunctions.begin(); fitnessFunction != getOptions().fitnessFunctions.end(); fitnessFunction++)
		{
			(*fitnessFunction)->setLogger(*options->logger);
		}

		for (auto creationCommand = getOptions().creationCommands.begin(); creationCommand != getOptions().creationCommands.end(); creationCommand++)
		{
			(*creationCommand)->setLogger(*options->logger);
			(*creationCommand)->setRandomGenerator(*randomGenerator.get());
		}

		for (auto exitCondition = getOptions().exitConditions.begin(); exitCondition != getOptions().exitConditions.end(); exitCondition++)
		{
			(*exitCondition)->setLogger(*options->logger);
		}

		for (auto selectionCommand = getOptions().selectionCommands.begin(); selectionCommand != getOptions().selectionCommands.end(); selectionCommand++)
		{
			(*selectionCommand)->setLogger(*options->logger);
			(*selectionCommand)->setRandomGenerator(*randomGenerator.get());
		}
	}

	bool EvolutionLearningRule::hasLearningSucceeded()
	{
		return exitConditionReached;
	}

	void EvolutionLearningRule::initializeTry()
	{
		// Reset all
		getOptions().world->clearPopulation();
		getOptions().world->initializeForLearning();
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
		std::vector<std::string> worldLabels = getOptions().world->getDataSetLabels();
		labels.insert(labels.end(), worldLabels.begin(), worldLabels.end());
		return labels;
	}

	void EvolutionLearningRule::setLogger(AbstractLogger& logger)
	{
		AbstractLearningRule::setLogger(logger);
		setHelperToUsedObjects();
	}

	bool EvolutionLearningRule::doIteration()
	{
		if (!options->disabledDataSets[getOptions().dataSetsPrefix + DATA_SET_FITNESS] && getOptions().world->getPopulationSize() > 0)
			learningState->addData(getOptions().dataSetsPrefix + DATA_SET_FITNESS, getOptions().world->getHighscoreList().front().first);


		log("------------- Generation " + std::to_string(learningState->iterations) + " -----------------", LL_LOW);

		if (getOptions().world->getPopulationSize() > 0) {
			// Extract all current objects ordered by their score
			const Highscore& highscore = getOptions().world->getHighscoreList();
			// This vector will contain all objects for the next generation
			std::vector<AbstractEvolutionObject*> newObjectVector;
			std::map<AbstractEvolutionObject*, int> operationCounter;

			// 5. Step: Reuse some of the evolution objects directly for the next generation
			for (auto reuseCommand = getOptions().reuseCommands.begin(); reuseCommand != getOptions().reuseCommands.end(); reuseCommand++)
			{
				(*reuseCommand)->select(highscore, operationCounter);
			}

			// 6. Step: Mutate some of the evolution objects and use them for the next getOptions()
			for (auto mutationCommand = getOptions().mutationsCommands.begin(); mutationCommand != getOptions().mutationsCommands.end(); mutationCommand++)
			{
				(*mutationCommand)->select(highscore, operationCounter);
			}

			// 7. Step: Combine some pairs of evolution objects and use the created ones for the next generation
			for (auto recombinationCommand = getOptions().recombinationCommands.begin(); recombinationCommand != getOptions().recombinationCommands.end(); recombinationCommand++)
			{
				(*recombinationCommand)->select(highscore, operationCounter);
			}

			for (auto object = getOptions().world->getEvolutionObjects().begin(); object != getOptions().world->getEvolutionObjects().end(); object++)
			{
				if (operationCounter[*object] == 0)
					notUsedObjects.push_back(*object);
			}

			// 7. Step: Combine some pairs of evolution objects and use the created ones for the next generation
			for (auto recombinationCommand = getOptions().recombinationCommands.begin(); recombinationCommand != getOptions().recombinationCommands.end(); recombinationCommand++)
			{
				(*recombinationCommand)->execute(newObjectVector, operationCounter, notUsedObjects);
			}

			// 6. Step: Mutate some of the evolution objects and use them for the next generation
			for (auto mutationCommand = getOptions().mutationsCommands.begin(); mutationCommand != getOptions().mutationsCommands.end(); mutationCommand++)
			{
				(*mutationCommand)->execute(newObjectVector, operationCounter, notUsedObjects);
			}

			// 5. Step: Reuse some of the evolution objects directly for the next generation
			for (auto reuseCommand = getOptions().reuseCommands.begin(); reuseCommand != getOptions().reuseCommands.end(); reuseCommand++)
			{
				(*reuseCommand)->execute(newObjectVector, operationCounter, notUsedObjects);
			}

			// Replace all evolution objects from the last generation with the one from the next generation
			getOptions().world->setEvolutionObjects(newObjectVector);
		}


		// 1. Step: Create new evolution objects
		for (auto creationCommand = getOptions().creationCommands.begin(); creationCommand != getOptions().creationCommands.end(); creationCommand++)
		{
			(*creationCommand)->execute(*getOptions().world, notUsedObjects);
		}

		// Reset the world for the next generation
		getOptions().world->reset();

		// 2. Step: Execute the simulation and try to rate the evolution objects
		if (getOptions().world->doSimulationStep()) {
			log(std::to_string(learningState->iterations) + " generations", LL_HIGH);
			learningState->iterations = 0;
			return true;
		}
		getOptions().world->refreshHighscore();

		// Extract all current objects ordered by their score
		Highscore& highscore = getOptions().world->getHighscoreList();

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
			return false;
		}



		// 4. Step: Select the relevant evolution objects (Other objects will be deleted)
		for (auto selectionCommand = getOptions().selectionCommands.begin(); selectionCommand != getOptions().selectionCommands.end(); selectionCommand++)
		{
			(*selectionCommand)->execute(highscore, getOptions().world->getEvolutionObjects(), notUsedObjects);
		}

		// Continue with the next generation
		learningState->iterations++;
		return true;
	}

	const EvolutionLearningRuleOptions& EvolutionLearningRule::getOptions() const
	{
		return static_cast<EvolutionLearningRuleOptions&>(*options.get());
	}

	void EvolutionLearningRule::doCalculationAfterLearningProcess()
	{
		if (!options->disabledDataSets[getOptions().dataSetsPrefix + DATA_SET_FITNESS])
			learningState->addData(getOptions().dataSetsPrefix + DATA_SET_FITNESS, getOptions().world->getHighscoreList().front().first);
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
