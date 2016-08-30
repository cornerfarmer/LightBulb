// Includes
#include "Learning/Reinforcement/PolicyGradientLearningRule.hpp"
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

AbstractLearningResult* PolicyGradientLearningRule::getLearningResult()
{
	EvolutionLearningResult* learningResult = new EvolutionLearningResult();
	
	return learningResult;
}

PolicyGradientLearningRule::PolicyGradientLearningRule(PolicyGradientLearningRuleOptions& options_)
	: AbstractReinforcementLearningRule(new PolicyGradientLearningRuleOptions(options_))
{
	initialize();
}

PolicyGradientLearningRule::PolicyGradientLearningRule(PolicyGradientLearningRuleOptions* options_)
	: AbstractReinforcementLearningRule(options_)
{
	initialize();
}

PolicyGradientLearningRule::PolicyGradientLearningRule()
	: AbstractReinforcementLearningRule(new PolicyGradientLearningRuleOptions())
{
	initialize();
}

void PolicyGradientLearningRule::initialize()
{
	//resilientLearningRateHelper.reset(new ResilientLearningRateHelper(new ResilientLearningRateHelperOptions()));
}

void PolicyGradientLearningRule::recordStep(AbstractNetworkTopology* networkTopology)
{
	errorVectorRecord.push_back(getErrorVector(networkTopology));

	netInputRecord.push_back(*networkTopology->getNetInputs());
	activationRecord.push_back(networkTopology->getActivationsCopy());
}

std::vector<Eigen::MatrixXd> PolicyGradientLearningRule::checkGradient(AbstractNetworkTopology* networkTopology)
{
	double epsilon = 0.0001;
	auto weights = networkTopology->getWeights();
	std::vector<Eigen::MatrixXd> gradientApprox(weights->size());
	for (int l = weights->size() - 1; l >= 0 ; l--)
	{
		gradientApprox[l].resizeLike(weights->at(l));
		for (int n1 = 0; n1 < weights->at(l).rows(); n1++)
		{
			for (int n2 = 0; n2 < weights->at(l).cols(); n2++)
			{
				weights->at(l)(n1, n2) += epsilon;
				getOptions()->world->doNNCalculation(false);
				double firstError = 0.5* getErrorVector(networkTopology).cwiseAbs2().sum();

				weights->at(l)(n1, n2) -= epsilon * 2;
				getOptions()->world->doNNCalculation(false);
				double secondError = 0.5* getErrorVector(networkTopology).cwiseAbs2().sum();
				gradientApprox[l](n1, n2) = (firstError - secondError) / (2 * epsilon);

				weights->at(l)(n1, n2) += epsilon;
			}
		}
	}
	return gradientApprox;
}

Eigen::VectorXd PolicyGradientLearningRule::getErrorVector(AbstractNetworkTopology* networkTopology)
{
	std::vector<double> lastOutput(networkTopology->getOutputSize());
	networkTopology->getOutput(lastOutput);

	Eigen::VectorXd errorVector(lastOutput.size());
	for (int i = 0; i < lastOutput.size(); i++)
	{
		errorVector(i) = getOptions()->world->getLastBooleanOutput()[i] - lastOutput[i];//-2 * std::signbit(getOptions()->world->getLastBooleanOutput()[i] - lastOutput[i]) + 1;
	}
	return errorVector;
}

void PolicyGradientLearningRule::initializeTry()
{
	//resilientLearningRateHelper->initialize(*getOptions()->world->getNeuralNetwork());
	getOptions()->world->setLearningState(learningState.get());
	getOptions()->world->initializeForLearning();

	gradients.resize(getOptions()->world->getNeuralNetwork()->getNetworkTopology()->getLayerCount() - 1);
	for (int i = 0; i < gradients.size(); i++)
	{
		gradients[i].resizeLike(getOptions()->world->getNeuralNetwork()->getNetworkTopology()->getWeights()->at(i));
	}
	resetGradients();

	stepsSinceLastReward = 0;
}


void PolicyGradientLearningRule::resetGradients()
{
	for (int i = 0; i < gradients.size(); i++)
	{
		gradients[i].setZero();
	}
}


std::string PolicyGradientLearningRule::getName()
{
	return "PolicyGradientLearningRule";
}

std::vector<std::string> PolicyGradientLearningRule::getDataSetLabels()
{
	std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
	labels.push_back(DATA_SET_GRADIENT);
	return labels;
}


bool PolicyGradientLearningRule::doIteration()
{
	int rewardCounter = 0;
	double totalReward = 0;
	AbstractNetworkTopology* networkTopology = getOptions()->world->getNeuralNetwork()->getNetworkTopology();

	while (rewardCounter < getOptions()->episodeSize)
	{
		double reward = getOptions()->world->doSimulationStep();
		
		recordStep(networkTopology);
		
		stepsSinceLastReward++;		
		
		if (reward != 0)
		{
			totalReward += reward;

			computeGradients(networkTopology, stepsSinceLastReward, reward);

			stepsSinceLastReward = 0;
			rewardCounter++;
		}
	}


	learningState->addData(DATA_SET_REWARD, totalReward);


	addGradients(networkTopology, gradients);
	resetGradients();
	
	
	// Continue with the next generation
	learningState->iterations++;

	getOptions()->world->rateKI();	

	return true;
}


void PolicyGradientLearningRule::addGradients(AbstractNetworkTopology* networkTopology, std::vector<Eigen::MatrixXd>& gradients)
{


	static std::vector<Eigen::MatrixXd> prevDeltaWeights(gradients.size());
	for (int l = gradients.size() - 1; l >= 0; l--)
	{
		if (prevDeltaWeights[l].size() == 0) {
			prevDeltaWeights[l].resizeLike(gradients[l]);
			prevDeltaWeights[l].setZero();
		}

		prevDeltaWeights[l] = 0.99 * prevDeltaWeights[l] + (1 - 0.99) * gradients[l].cwiseAbs2();

/*
		prevDeltaWeights[l] = resilientLearningRateHelper->getLearningRate(l + 1, gradients[l]);*/
		
		Eigen::MatrixXd newWeights = networkTopology->getAfferentWeightsPerLayer(l + 1) - 1e-2 * gradients[l].cwiseQuotient((prevDeltaWeights[l].cwiseSqrt().array() + 1e-5).matrix());
		networkTopology->setAfferentWeightsPerLayer(l + 1, newWeights);
		
		gradients[l] *= 1.0 / getOptions()->episodeSize;
	}

	learningState->addData(DATA_SET_GRADIENT, gradients.back()(0, 0));
}

PolicyGradientLearningRuleOptions* PolicyGradientLearningRule::getOptions()
{
	return static_cast<PolicyGradientLearningRuleOptions*>(options.get());
}

void PolicyGradientLearningRule::doCalculationAfterLearningProcess()
{
}

void PolicyGradientLearningRule::computeGradients(AbstractNetworkTopology* networkTopology, int stepsSinceLastReward, double reward)
{
	Eigen::VectorXd rewards(stepsSinceLastReward);
	rewards(stepsSinceLastReward - 1) = reward;
	for (int i = stepsSinceLastReward - 2; i >= 0; i--)
	{
		rewards(i) = rewards(i + 1) * 0.99;
	}

	//rewards = rewards.array() - rewards.mean();
	//double stddev = std::sqrt(rewards.cwiseAbs2().sum() / stepsSinceLastReward);
	//rewards = rewards.array() / stddev;

	for (int i = 0; i < stepsSinceLastReward; i++)
	{
		errorVectorRecord[i] = rewards(i) * errorVectorRecord[i].array();
		computeGradientsForError(networkTopology, errorVectorRecord[i], netInputRecord[i], activationRecord[i]);
	}

	errorVectorRecord.clear();
	netInputRecord.clear();
	activationRecord.clear();
}

void PolicyGradientLearningRule::computeGradientsForError(AbstractNetworkTopology* networkTopology, Eigen::VectorXd& errorVector, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::VectorXd>& activations)
{
	std::vector<Eigen::MatrixXd> deltaVectorOutputLayer(networkTopology->getLayerCount());
	for (int layerIndex = networkTopology->getLayerCount() - 1; layerIndex > 0; layerIndex--)
	{
		// If its the last layer
		if (layerIndex == networkTopology->getLayerCount() - 1)
		{
			// Compute the delta value: activationFunction'(netInput) * errorValue
			deltaVectorOutputLayer[layerIndex] = (networkTopology->getOutputActivationFunction()->executeDerivation(netInputs[layerIndex]).array() + 0.1) * errorVector.array();
		}
		else
		{
			Eigen::VectorXd nextLayerErrorValueFactor = networkTopology->getEfferentWeightsPerLayer(layerIndex) * deltaVectorOutputLayer[layerIndex + 1];

			// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
			deltaVectorOutputLayer[layerIndex] = (networkTopology->getInnerActivationFunction()->executeDerivation(netInputs[layerIndex]).array() + 0.1) * nextLayerErrorValueFactor.tail(nextLayerErrorValueFactor.rows() - networkTopology->usesBiasNeuron()).array();
		}

		// Calculate the gradient
		// gradient = - Output(prevNeuron) * deltaValue
		Eigen::MatrixXd gradient = (deltaVectorOutputLayer[layerIndex] * activations[layerIndex - 1].transpose()).matrix();
		gradient *= -1;
		gradients[layerIndex - 1] += gradient;
	}

	/*std::vector<Eigen::MatrixXd> gradientApprox = checkGradient(networkTopology);
	std::vector<Eigen::MatrixXd> diff(gradientApprox.size());
	bool same = true;
	for (int i = 0; i < gradientApprox.size(); i++)
	{
		diff[i] = gradients[i] - gradientApprox[i];
		same &= gradients[i].isApprox(gradientApprox[i], 1e-8);
	}
	if (!same)
		throw std::logic_error("");*/
	
}

