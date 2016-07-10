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
	initialize();
}

ReinforcementLearningRule::ReinforcementLearningRule(ReinforcementLearningRuleOptions* options_)
	: AbstractLearningRule(options_)
{
	initialize();
}

ReinforcementLearningRule::ReinforcementLearningRule()
	: AbstractLearningRule(new ReinforcementLearningRuleOptions())
{
	initialize();
}

void ReinforcementLearningRule::initialize()
{
	resilientLearningRateHelper.reset(new ResilientLearningRateHelper(new ResilientLearningRateHelperOptions()));
}

bool ReinforcementLearningRule::hasLearningSucceeded()
{
	return false;
}

void ReinforcementLearningRule::initializeTry()
{
	resilientLearningRateHelper->initialize(*getOptions()->world->getNeuralNetwork());
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

	while (rewardCounter < 10)
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
	static std::vector<Eigen::MatrixXd> prevDeltaWeights(gradients.size());
	for (int l = 0; l < gradients.size(); l++)
	{
		gradients[l] *= 1.0 / stepsSinceLastReward;

	/*	if (prevDeltaWeights[l].size() == 0) {
			prevDeltaWeights[l].resizeLike(gradients[l]);
			prevDeltaWeights[l].setZero();
		}

		prevDeltaWeights[l] = 0.99 * prevDeltaWeights[l] + (1 - 0.99) * gradients[l].cwiseAbs2();
*/

		prevDeltaWeights[l] = resilientLearningRateHelper->getLearningRate(l + 1, gradients[l]);
		
		Eigen::MatrixXd newWeights = networkTopology->getAfferentWeightsPerLayer(l + 1) + prevDeltaWeights[l];// 1e-4 * gradients[l].cwiseQuotient((prevDeltaWeights[l].cwiseSqrt().array() + 1e-5).matrix());
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
		positiveOutputVector(i) = getOptions()->world->getLastBooleanOutput()[i] - lastOutput[i];
	}

	Eigen::VectorXd negativeOutputVector(lastOutput.size());
	for (int i = 0; i < lastOutput.size(); i++)
	{
		negativeOutputVector(i) = getOptions()->world->getLastBooleanOutput()[i] - lastOutput[i];
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

