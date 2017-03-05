// Includes
#include "LightBulb/Learning/Reinforcement/PolicyGradientLearningRule.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningResult.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/Function/ActivationFunction/RectifierFunction.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/Learning/LearningState.hpp"
#include "LightBulb/Function/ActivationFunction/IdentityFunction.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementIndividual.hpp"

namespace LightBulb
{
	AbstractLearningResult* PolicyGradientLearningRule::getLearningResult()
	{
		EvolutionLearningResult* learningResult = new EvolutionLearningResult();

		return learningResult;
	}


	PolicyGradientLearningRule::PolicyGradientLearningRule(PolicyGradientLearningRuleOptions& options_)
		: AbstractReinforcementLearningRule(new PolicyGradientLearningRuleOptions(options_))
	{
		initialize(static_cast<PolicyGradientLearningRuleOptions&>(*options.get()));
	}

	PolicyGradientLearningRule::PolicyGradientLearningRule(PolicyGradientLearningRuleOptions* options_)
		: AbstractReinforcementLearningRule(options_)
	{
		initialize(*options_);
	}

	PolicyGradientLearningRule::PolicyGradientLearningRule()
		: AbstractReinforcementLearningRule(new PolicyGradientLearningRuleOptions())
	{
		initialize(static_cast<PolicyGradientLearningRuleOptions&>(*options.get()));
	}

	PolicyGradientLearningRule::~PolicyGradientLearningRule() = default;

	void PolicyGradientLearningRule::initialize(PolicyGradientLearningRuleOptions& options)
	{
		getErrorVectorKernel.reset(new Kernel("policy_gradient_learning_rule", "get_error_vector"));
		computeNextRecordIndexKernel.reset(new Kernel("policy_gradient_learning_rule", "compute_next_record_index"));
		computeRewardsKernel.reset(new Kernel("policy_gradient_learning_rule", "compute_rewards"));
		computeNextRecordStartKernel.reset(new Kernel("policy_gradient_learning_rule", "compute_next_record_start"));
		computeGradientsKernel.reset(new Kernel("policy_gradient_learning_rule", "compute_gradients"));

		recordStart.getEigenValueForEditing() = 0;
		nextRecordIndex.getEigenValueForEditing() = 0;

		gradientCalculation.reset(new Backpropagation());
		gradientCalculation->setCalculatorType(getOptions().calculatorType);
		gradientDescentAlgorithm.reset(new RMSPropLearningRate(options.rmsPropLearningRateOptions));
		gradientDescentAlgorithm->setCalculatorType(getOptions().calculatorType);

		valueFunctionGradientCalculation.reset(new Backpropagation());
		valueFunctionGradientDescentAlgorithm.reset(new RMSPropLearningRate(options.valueRmsPropLearningRateOptions));

		getOptions().environment->setCalculatorType(getOptions().calculatorType);
	}

	void PolicyGradientLearningRule::initializeLearningAlgoritm()
	{
		gradientDescentAlgorithm->initialize(getOptions().individual->getNeuralNetwork().getNetworkTopology());
		gradientCalculation->initWithExternalGradient(getOptions().individual->getNeuralNetwork().getNetworkTopology());
		stateRecord.getEigenValueForEditing().resize(getOptions().individual->getNeuralNetwork().getNetworkTopology().getInputSize(), getBufferSize());
		rewardRecord.getEigenValueForEditing().resize(getBufferSize());
		isTerminalStateRecord.getEigenValueForEditing().resize(getBufferSize());
		errorVector.getEigenValueForEditing().resize(getOptions().individual->getNeuralNetwork().getNetworkTopology().getOutputSize());
		tmpGradient = getOptions().individual->getNeuralNetwork().getNetworkTopology().getAllWeights();
		gradient = getOptions().individual->getNeuralNetwork().getNetworkTopology().getAllWeights();

		gradientRecord.clear();
		for (auto layer = getOptions().individual->getNeuralNetwork().getNetworkTopology().getAllWeights().begin(); layer != getOptions().individual->getNeuralNetwork().getNetworkTopology().getAllWeights().end(); layer++)
			gradientRecord.push_back(Tensor<>(getBufferSize(), layer->getEigenValue().rows(), layer->getEigenValue().cols()));

		if (getOptions().valueFunctionAsBase)
		{
			FeedForwardNetworkTopologyOptions options;
			options.enableShortcuts = false;
			options.useBiasNeuron = true;

			options.neuronsPerLayerCount.push_back(6);
			options.neuronsPerLayerCount.push_back(256);
			options.neuronsPerLayerCount.push_back(1);

			options.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new RectifierFunction()), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
			
			valueFunctionNetwork.reset(new NeuralNetwork(new FeedForwardNetworkTopology(options)));
			valueFunctionGradientDescentAlgorithm->initialize(valueFunctionNetwork->getNetworkTopology());
		}
	}

	void PolicyGradientLearningRule::recordStep(AbstractNetworkTopology& networkTopology, Scalar<>& reward)
	{
		getErrorVector(networkTopology, errorVector);
		
		if (getOptions().calculatorType == CT_GPU) 
		{
			copyVectorToMatrixCol(stateRecord.getViennaclValueForEditing(), getOptions().individual->getLastInput().getViennaclValue(), nextRecordIndex.getViennaclValue());

			copyScalarToVectorElement(rewardRecord.getViennaclValueForEditing(), reward.getViennaclValue(), nextRecordIndex.getViennaclValue());

			getOptions().individual->isTerminalState(isTerminalState);
			copyScalarToVectorElement(isTerminalStateRecord.getViennaclValueForEditing(), isTerminalState.getViennaclValue(), nextRecordIndex.getViennaclValue());

			for (int i = 0; i < tmpGradient.size(); i++)
				tmpGradient[i].getViennaclValueForEditing().clear();

			gradientCalculation->calcGradient(networkTopology, errorVector, tmpGradient, &getOptions().individual->getLastInput());

			for (int i = 0; i < tmpGradient.size(); i++)
				copyMatrixToTensorArea(gradientRecord[i].getViennaclValueForEditing(), tmpGradient[i].getViennaclValue(), nextRecordIndex.getViennaclValue());


			viennacl::ocl::enqueue(computeNextRecordIndexKernel->use()(
				viennacl::traits::opencl_handle(nextRecordIndex.getViennaclValueForEditing()),
				cl_uint(getBufferSize())
			));
			
		}
		else
		{
			stateRecord.getEigenValueForEditing().col(nextRecordIndex.getEigenValue()) = getOptions().individual->getLastInput().getEigenValue();

			rewardRecord.getEigenValueForEditing()[nextRecordIndex.getEigenValue()] = reward.getEigenValue();

			getOptions().individual->isTerminalState(isTerminalState);
			isTerminalStateRecord.getEigenValueForEditing()[nextRecordIndex.getEigenValue()] = isTerminalState.getEigenValue();

			for (int i = 0; i < tmpGradient.size(); i++)
				tmpGradient[i].getEigenValueForEditing().setZero();
			
			gradientCalculation->calcGradient(networkTopology, errorVector, tmpGradient, &getOptions().individual->getLastInput());

			for (int i = 0; i < tmpGradient.size(); i++)
				gradientRecord[i].getEigenValueForEditing()[nextRecordIndex.getEigenValue()] = tmpGradient[i].getEigenValue();

			nextRecordIndex.getEigenValueForEditing()++;
			nextRecordIndex.getEigenValueForEditing() %= getBufferSize();
		}
	}

	int PolicyGradientLearningRule::getBufferSize()
	{
		return getOptions().episodeSize + getOptions().maxEpisodeLength;
	}

	void PolicyGradientLearningRule::getErrorVector(AbstractNetworkTopology& networkTopology, Vector<>& errorVector)
	{
		if (getOptions().calculatorType == CT_GPU)
		{
			viennacl::ocl::enqueue(getErrorVectorKernel->use()(
				viennacl::traits::opencl_handle(errorVector.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(getOptions().individual->getLastBooleanOutput().getViennaclValue()),
				viennacl::traits::opencl_handle(networkTopology.getAllActivations().back().getViennaclValue()),
				cl_uint(viennacl::traits::size(networkTopology.getAllActivations().back().getViennaclValue()))
			));
		}
		else
		{
			for (int i = 0; i < networkTopology.getAllActivations().back().getEigenValue().size(); i++)
			{
				errorVector.getEigenValueForEditing()(i) = getOptions().individual->getLastBooleanOutput().getEigenValue()(i) - networkTopology.getAllActivations().back().getEigenValue()[i];//-2 * std::signbit(getOptions()->environment->getLastBooleanOutput()[i] - lastOutput[i]) + 1;
			}
			errorSum += errorVector.getEigenValueForEditing().cwiseAbs().sum();
		}
		errorSteps++;
	}

	void PolicyGradientLearningRule::initializeTry()
	{
		//resilientLearningRateHelper->initialize(*getOptions()->environment->getNeuralNetwork());
		getOptions().environment->setLearningState(*learningState.get());
		getOptions().environment->initializeForLearning();
		getOptions().individual->initializeForLearning();

		recordStart.getEigenValueForEditing() = 0;
		nextRecordIndex.getEigenValueForEditing() = 0;

		if (getOptions().valueFunctionAsBase)
		{
			valueFunctionNetwork->getNetworkTopology().randomizeDependingOnLayerSize(*randomGenerator.get());
		}
	}

	
	std::string PolicyGradientLearningRule::getName()
	{
		return "PolicyGradientLearningRule";
	}

	std::vector<std::string> PolicyGradientLearningRule::getDataSetLabels() const
	{
		std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
		labels.push_back(DATA_SET_ERROR_AVG);
		if (getOptions().valueFunctionAsBase)
			labels.push_back(DATA_SET_VALUE_ERROR_AVG);
		return labels;
	}


	void PolicyGradientLearningRule::doIteration()
	{
		errorSum = 0;
		valueErrorSum = 0;
		errorSteps = 0;
		valueErrorSteps = 0;
		AbstractNetworkTopology& networkTopology = getOptions().individual->getNeuralNetwork().getNetworkTopology();
		
		if (getOptions().calculatorType == CT_GPU)
		{
			totalReward.getViennaclValueForEditing() -= totalReward.getViennaclValue();
			for (int i = 0; i < gradient.size(); i++)
				gradient[i].getViennaclValueForEditing().clear();
		}
		else
		{
			totalReward.getEigenValueForEditing() = 0;
			for (int i = 0; i < gradient.size(); i++)
				gradient[i].getEigenValueForEditing().setZero();
		}


		if (getOptions().valueFunctionAsBase)
			valueFunctionGradientCalculation->initGradient(valueFunctionNetwork->getNetworkTopology());

		for (int i = 0; i < getOptions().episodeSize; i++)
		{
			getOptions().individual->doSimulationStep();
			getOptions().environment->doSimulationStep();
			getOptions().individual->getReward(reward);

			recordStep(networkTopology, reward);

			if (getOptions().calculatorType == CT_GPU)
				totalReward.getViennaclValueForEditing() += reward.getViennaclValue();
			else
				totalReward.getEigenValueForEditing() += reward.getEigenValue();

			if (getOptions().calculatorType == CT_CPU && nextRecordIndex.getEigenValue() == recordStart.getEigenValue())
				throw std::logic_error("An epsiode has been longer then the configured maxEpisodeLength.");
		}
		
		if (getOptions().calculatorType == CT_CPU || learningState->iterations % getOptions().logInterval == 0)
			learningState->addData(DATA_SET_REWARD, totalReward.getEigenValue());

		learningState->addData(DATA_SET_ERROR_AVG, errorSum / errorSteps);
		if (getOptions().valueFunctionAsBase)
			learningState->addData(DATA_SET_VALUE_ERROR_AVG, valueErrorSum / valueErrorSteps);

		computeGradients();
		addGradients(networkTopology);

		if (learningState->iterations % getOptions().ratingInterval == 0)
		{
			getOptions().individual->setStochasticActionDecision(false);
			getOptions().individual->rate();
			getOptions().individual->setStochasticActionDecision(true);
		}
	}


	void PolicyGradientLearningRule::addGradients(AbstractNetworkTopology& networkTopology)
	{
		for (int l = gradient.size() - 1; l >= 0; l--)
		{
			gradientDescentAlgorithm->adjustWeights(networkTopology, networkTopology.getAllWeights()[l], l + 1, gradient[l]);
		}

		if (getOptions().valueFunctionAsBase)
		{
			for (int l = valueFunctionGradientCalculation->getGradient().size() - 1; l >= 0; l--)
			{
				valueFunctionGradientDescentAlgorithm->adjustWeights(valueFunctionNetwork->getNetworkTopology(), valueFunctionNetwork->getNetworkTopology().getAllWeights()[l], l + 1, valueFunctionGradientCalculation->getGradient().at(l));
			}
		}
	}

	const PolicyGradientLearningRuleOptions& PolicyGradientLearningRule::getOptions() const
	{
		return static_cast<PolicyGradientLearningRuleOptions&>(*options.get());
	}

	void PolicyGradientLearningRule::doCalculationAfterLearningProcess()
	{
	}

	void PolicyGradientLearningRule::computeGradients()
	{
		if (getOptions().calculatorType == CT_GPU)
		{
			viennacl::ocl::enqueue(computeRewardsKernel->use()(
				viennacl::traits::opencl_handle(rewardRecord.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(isTerminalStateRecord.getViennaclValue()),
				viennacl::traits::opencl_handle(recordStart.getViennaclValue()),
				viennacl::traits::opencl_handle(nextRecordIndex.getViennaclValue()),
				viennacl::traits::opencl_handle(lastRelevantIndex.getViennaclValueForEditing()),
				cl_uint(getBufferSize())
			));

			for (int j = 0; j < gradientRecord.size(); j++)
			{
				viennacl::ocl::enqueue(computeGradientsKernel->use()(
					viennacl::traits::opencl_handle(gradient[j].getViennaclValue()),
					cl_uint(viennacl::traits::size1(gradient[j].getViennaclValue())),
					cl_uint(viennacl::traits::size2(gradient[j].getViennaclValue())),
					cl_uint(viennacl::traits::internal_size2(gradient[j].getViennaclValue())),
					viennacl::traits::opencl_handle(gradientRecord[j].getViennaclValue()),
					cl_uint(viennacl::traits::internal_size2(gradientRecord[j].getViennaclValue())),
					viennacl::traits::opencl_handle(rewardRecord.getViennaclValue()),
					viennacl::traits::opencl_handle(recordStart.getViennaclValue()),
					viennacl::traits::opencl_handle(nextRecordIndex.getViennaclValue()),
					viennacl::traits::opencl_handle(lastRelevantIndex.getViennaclValueForEditing()),
					cl_uint(getBufferSize())
				));
			}

			viennacl::ocl::enqueue(computeNextRecordIndexKernel->use()(
				viennacl::traits::opencl_handle(recordStart.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(lastRelevantIndex.getViennaclValue()),
				cl_uint(getBufferSize())
			));
			
		}
		else
		{
			lastRelevantIndex.getEigenValueForEditing() = -1;
			int i = nextRecordIndex.getEigenValue() - 1;
			do
			{
				if (i < 0)
					i = getBufferSize() - 1;

				if (lastRelevantIndex.getEigenValue() == -1 && isTerminalStateRecord.getEigenValue()[i])
					lastRelevantIndex.getEigenValueForEditing() = i;
				if (lastRelevantIndex.getEigenValue() != -1)
				{
					if (!isTerminalStateRecord.getEigenValue()[i])
						rewardRecord.getEigenValueForEditing()[i] += rewardRecord.getEigenValue()[(i + 1) % getBufferSize()] * 0.99;
				}
				i--;
			} while (i != recordStart.getEigenValue() - 1);

			if (lastRelevantIndex.getEigenValue() == -1)
				throw std::logic_error("There has been no terminal states in the last " + std::to_string(getBufferSize()) + " steps.");

			/*	rewards = rewards.array() - rewards.mean();
				double stddev = std::sqrt(rewards.cwiseAbs2().sum() / stepsSinceLastReward);
				rewards = rewards.array() / stddev;*/

			for (i = recordStart.getEigenValue(); i != (lastRelevantIndex.getEigenValue() + 1) % getBufferSize(); i++, i %= getBufferSize())
			{
				if (getOptions().valueFunctionAsBase)
				{
					tmp.getEigenValueForEditing() = stateRecord.getEigenValue().col(i);
					Vector<> output = valueFunctionNetwork->calculateWithoutOutputCopy(tmp, TopologicalOrder());

					Vector<> errorVector(1);
					errorVector.getEigenValueForEditing()(0) = rewardRecord.getEigenValue()[i] - output.getEigenValue()[0];
					valueFunctionGradientCalculation->calcGradient(valueFunctionNetwork->getNetworkTopology(), errorVector);
					valueErrorSum += abs(errorVector.getEigenValue()(0));
					valueErrorSteps++;

					rewardRecord.getEigenValueForEditing()[i] -= output.getEigenValue()[0];
				}

				for (int j = 0; j < gradientRecord.size(); j++)
					gradient[j].getEigenValueForEditing().noalias() = gradient[j].getEigenValue() + gradientRecord[j].getEigenValue()[i] * rewardRecord.getEigenValue()[i];
			}

			recordStart.getEigenValueForEditing() = (lastRelevantIndex.getEigenValue() + 1) % getBufferSize();
		}
	}


}
