// Includes
#include "Learning/Reinforcement/ReinforcementLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
// Library includes
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <Learning/EvolutionLearningResult.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include "AbstractReinforcementWorld.hpp"

AbstractLearningResult* ReinforcementLearningRule::getLearningResult()
{
	EvolutionLearningResult* learningResult = new EvolutionLearningResult();
	
	return learningResult;
}

ReinforcementLearningRule::ReinforcementLearningRule(ReinforcementLearningRuleOptions& options_)
	: AbstractLearningRule(new ReinforcementLearningRuleOptions(options_))
{
}

ReinforcementLearningRule::ReinforcementLearningRule(ReinforcementLearningRuleOptions* options_)
	: AbstractLearningRule(options_)
{
}

ReinforcementLearningRule::ReinforcementLearningRule()
	: AbstractLearningRule(new ReinforcementLearningRuleOptions())
{

}

bool ReinforcementLearningRule::hasLearningSucceeded()
{
	return false;
}

void ReinforcementLearningRule::initializeTry()
{
	getOptions()->world->setLearningState(learningState.get());
	getOptions()->world->initializeForLearning();

	gradientsNegative.resize(getOptions()->world->getNeuralNetwork()->getNetworkTopology()->getLayerCount() - 1);
	gradientsPositive.resize(gradientsNegative.size());
	for (int i = 0; i < gradientsNegative.size(); i++)
	{
		gradientsNegative[i].resizeLike(getOptions()->world->getNeuralNetwork()->getNetworkTopology()->getWeights()->at(i));
		gradientsPositive[i].resizeLike(gradientsNegative[i]);
	}
	resetGradients();

	stepsSinceLastReward = 0;
}


void ReinforcementLearningRule::resetGradients()
{
	for (int i = 0; i < gradientsNegative.size(); i++)
	{
		gradientsNegative[i].setZero();
		gradientsPositive[i].setZero();
	}
}


std::string ReinforcementLearningRule::getName()
{
	return "ReinforcementLearningRule";
}

std::vector<std::string> ReinforcementLearningRule::getDataSetLabels()
{
	std::vector<std::string> labels = AbstractLearningRule::getDataSetLabels();
	labels.push_back(DATA_SET_REWARD);
	std::vector<std::string> worldLabels = getOptions()->world->getDataSetLabels();
	labels.insert(labels.end(), worldLabels.begin(), worldLabels.end());
	return labels;
}


bool ReinforcementLearningRule::doIteration()
{
	int rewardCounter = 0;
	double totalReward = 0;
	AbstractNetworkTopology* networkTopology = getOptions()->world->getNeuralNetwork()->getNetworkTopology();

	while (rewardCounter < 100)
	{
		double reward = getOptions()->world->doSimulationStep();
		
		computeGradients(networkTopology);
		stepsSinceLastReward++;

		if (reward != 0)
		{
			totalReward += reward;

			if (reward > 0)
				gradientsNegative = gradientsPositive;
			else
				gradientsPositive = gradientsNegative;

			rewardCounter++;
		}
	}


	learningState->addData(DATA_SET_REWARD, totalReward);


	addGradients(networkTopology, gradientsPositive);
	resetGradients();
	stepsSinceLastReward = 0;
	
	// Continue with the next generation
	learningState->iterations++;

	getOptions()->world->rateKI();	

	return true;
}


void ReinforcementLearningRule::addGradients(AbstractNetworkTopology* networkTopology, std::vector<Eigen::MatrixXd>& gradients)
{
	for (int l = 0; l < gradients.size(); l++)
	{
		gradients[l] *= 1.0 / stepsSinceLastReward;

		Eigen::MatrixXd newWeights = networkTopology->getAfferentWeightsPerLayer(l + 1) - 10*gradients[l];
		networkTopology->setAfferentWeightsPerLayer(l + 1, newWeights);
	}
}

ReinforcementLearningRuleOptions* ReinforcementLearningRule::getOptions()
{
	return static_cast<ReinforcementLearningRuleOptions*>(options.get());
}

void ReinforcementLearningRule::doCalculationAfterLearningProcess()
{
}

void ReinforcementLearningRule::computeGradients(AbstractNetworkTopology* networkTopology)
{
	std::vector<double> lastOutput(networkTopology->getOutputSize());
	networkTopology->getOutput(lastOutput);

	Eigen::VectorXd positiveOutputVector(lastOutput.size());
	for (int i = 0; i < lastOutput.size(); i++)
	{
		if (lastOutput[i] > (networkTopology->getOutputActivationFunction()->getMaximum() - networkTopology->getOutputActivationFunction()->getMinimum()) / 2 + networkTopology->getOutputActivationFunction()->getMinimum())
			positiveOutputVector(i) = networkTopology->getOutputActivationFunction()->getMaximum() - lastOutput[i];
		else
			positiveOutputVector(i) = networkTopology->getOutputActivationFunction()->getMinimum() - lastOutput[i];
	}

	Eigen::VectorXd negativeOutputVector(lastOutput.size());
	for (int i = 0; i < lastOutput.size(); i++)
	{
		if (lastOutput[i] <= (networkTopology->getOutputActivationFunction()->getMaximum() - networkTopology->getOutputActivationFunction()->getMinimum()) / 2 + networkTopology->getOutputActivationFunction()->getMinimum())
			negativeOutputVector(i) = networkTopology->getOutputActivationFunction()->getMaximum() - lastOutput[i];
		else
			negativeOutputVector(i) = networkTopology->getOutputActivationFunction()->getMinimum() - lastOutput[i];
	}

	computeGradientsForError(networkTopology, positiveOutputVector, gradientsPositive);
	computeGradientsForError(networkTopology, negativeOutputVector, gradientsNegative);
	
}

void ReinforcementLearningRule::computeGradientsForError(AbstractNetworkTopology* networkTopology, Eigen::VectorXd& errorVector, std::vector<Eigen::MatrixXd>& gradients)
{
	std::vector<Eigen::MatrixXd> deltaVectorOutputLayer(networkTopology->getLayerCount());
	for (int layerIndex = networkTopology->getLayerCount() - 1; layerIndex > 0; layerIndex--)
	{
		// If its the last layer
		if (layerIndex == networkTopology->getLayerCount() - 1)
		{
			// Compute the delta value: activationFunction'(netInput) * errorValue
			deltaVectorOutputLayer[layerIndex] = (networkTopology->getOutputActivationFunction()->executeDerivation(networkTopology->getNetInputVector(layerIndex)).array() + 0.1) * errorVector.array();
		}
		else
		{
			Eigen::VectorXd nextLayerErrorValueFactor = networkTopology->getEfferentWeightsPerLayer(layerIndex) * deltaVectorOutputLayer[layerIndex + 1];

			// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
			deltaVectorOutputLayer[layerIndex] = (networkTopology->getInnerActivationFunction()->executeDerivation(networkTopology->getNetInputVector(layerIndex)).array() + 0.1) * nextLayerErrorValueFactor.tail(nextLayerErrorValueFactor.rows() - networkTopology->usesBiasNeuron()).array();
		}

		// Calculate the gradient
		// gradient = - Output(prevNeuron) * deltaValue
		Eigen::MatrixXd gradient = (deltaVectorOutputLayer[layerIndex] * networkTopology->getActivationVector(layerIndex - 1).transpose()).matrix();
		gradient *= -1;
		gradients[layerIndex - 1] += gradient;
	}
}

