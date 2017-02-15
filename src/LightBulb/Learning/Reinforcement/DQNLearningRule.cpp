// Includes
#include "LightBulb/Learning/Reinforcement/DQNLearningRule.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningResult.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "LightBulb/Teaching/TeachingLessonLinearInput.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/Learning/Supervised/SupervisedLearningResult.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include "LightBulb/Teaching/Teacher.hpp"
#include "LightBulb/Logging/AbstractLogger.hpp"
#include "LightBulb/Learning/LearningState.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

// Library includes

namespace LightBulb
{

	void TransitionStorage::reset(int maxRecordNumber, int networkInputSize)
	{
		states.getEigenValueForEditing().resize(networkInputSize, maxRecordNumber);
		nextStates.getEigenValueForEditing().resize(networkInputSize, maxRecordNumber);
		actions.getEigenValueForEditing().resize(maxRecordNumber);
		isTerminalState.getEigenValueForEditing().resize(maxRecordNumber);
		rewards.getEigenValueForEditing().resize(maxRecordNumber);
	}

	AbstractLearningResult* DQNLearningRule::getLearningResult()
	{
		EvolutionLearningResult* learningResult = new EvolutionLearningResult();

		return learningResult;
	}

	DQNLearningRule::DQNLearningRule(DQNLearningRuleOptions& options_)
		: AbstractReinforcementLearningRule(new DQNLearningRuleOptions(options_))
	{
		initialize(static_cast<DQNLearningRuleOptions*>(options.get()));
	}

	DQNLearningRule::DQNLearningRule(DQNLearningRuleOptions* options_)
		: AbstractReinforcementLearningRule(options_)
	{
		initialize(options_);
	}

	DQNLearningRule::DQNLearningRule()
		: AbstractReinforcementLearningRule(new DQNLearningRuleOptions())
	{
	}

	DQNLearningRule::~DQNLearningRule() = default;


	void DQNLearningRule::initialize(DQNLearningRuleOptions* options)
	{
		teacher.reset(new Teacher());
		options->gradientDescentOptions.gradientDescentAlgorithm = new RMSPropLearningRate(options->rmsPropOptions);
		options->gradientDescentOptions.teacher = teacher.get();
		options->gradientDescentOptions.neuralNetwork = &getOptions().environment->getNeuralNetwork();
		options->gradientDescentOptions.logger = nullptr;
		options->gradientDescentOptions.calculatorType = getOptions().calculatorType;
		gradientDescent.reset(new GradientDescentLearningRule(options->gradientDescentOptions));

		getOptions().environment->setCalculatorType(getOptions().calculatorType);
		steadyNetwork.reset(getOptions().environment->getNeuralNetwork().clone());
	}

	void DQNLearningRule::initializeTry()
	{
		transitionStorage.reset(getOptions().replayMemorySize, getOptions().environment->getNeuralNetwork().getNetworkTopology().getInputSize());
		nextTransitionIndex = 0;
		transitionCounter = 0;
		tmp.getEigenValueForEditing().resize(getOptions().environment->getNeuralNetwork().getNetworkTopology().getInputSize());

		getOptions().environment->setLearningState(*learningState.get());
		getOptions().environment->initializeForLearning();
		steadyNetwork->getNetworkTopology().copyWeightsFrom(getOptions().environment->getNeuralNetwork().getNetworkTopology());
		
		waitUntilLearningStarts = getOptions().replayStartSize;
		getOptions().environment->setEpsilon(getOptions().initialExploration);
	}
	
	void DQNLearningRule::storeTransition(const AbstractNetworkTopology* networkTopology, const Scalar<>& reward)
	{		
		if (transitionCounter < getOptions().replayMemorySize || getOptions().replaceStoredTransitions)
		{
			int index = nextTransitionIndex++;
			nextTransitionIndex %= getOptions().replayMemorySize;
			if (transitionCounter < getOptions().replayMemorySize)
				transitionCounter++;

			if (getOptions().calculatorType == CT_GPU)
			{
				copyVectorToMatrixCol(transitionStorage.states.getViennaclValueForEditing(), getOptions().environment->getLastInput().getViennaclValue(), index);
				
				getOptions().environment->isTerminalState(isTerminalState);
				copyScalarToVectorElement(transitionStorage.isTerminalState.getViennaclValueForEditing(), isTerminalState.getViennaclValue(), index);

				getOptions().environment->getNNInput(tmp);
				copyVectorToMatrixCol(transitionStorage.nextStates.getViennaclValueForEditing(), tmp.getViennaclValue(), index);

				copyScalarToVectorElement(transitionStorage.rewards.getViennaclValueForEditing(), reward.getViennaclValue(), index);

				static viennacl::ocl::kernel& kernel = getKernel("dqn_learning_rule", "determine_action", "dqn_learning_rule.cl");

				viennacl::ocl::enqueue(kernel(
					viennacl::traits::opencl_handle(getOptions().environment->getLastBooleanOutput().getViennaclValue()),
					viennacl::traits::opencl_handle(transitionStorage.actions.getViennaclValueForEditing()),
					cl_uint(viennacl::traits::size(getOptions().environment->getLastBooleanOutput().getViennaclValue())),
					cl_uint(index)
				));

			}
			else
			{
				transitionStorage.states.getEigenValueForEditing().col(index) = getOptions().environment->getLastInput().getEigenValue();

				getOptions().environment->isTerminalState(isTerminalState);
				transitionStorage.isTerminalState.getEigenValueForEditing()[index] = isTerminalState.getEigenValue();

				if (!isTerminalState.getEigenValue()) {
					getOptions().environment->getNNInput(tmp);
					transitionStorage.nextStates.getEigenValueForEditing().col(index) = tmp.getEigenValue();
				}

				transitionStorage.rewards.getEigenValueForEditing()(index) = reward.getEigenValue();
			
				for (int i = 0; i < getOptions().environment->getLastBooleanOutput().getEigenValue().size(); i++)
				{
					if (getOptions().environment->getLastBooleanOutput().getEigenValue()[i])
					{
						transitionStorage.actions.getEigenValueForEditing()(index) = i;
						break;
					}
				}
			}
		}
	}

	void DQNLearningRule::doSupervisedLearning()
	{
		while (teachingLessonsInputs.size() < std::min(static_cast<int>(transitionCounter), getOptions().minibatchSize))
		{
			teachingLessonsInputs.push_back(new TeachingInput<>(steadyNetwork->getNetworkTopology().getOutputSize()));
			teachingLessonsPatterns.push_back(new Vector<>(steadyNetwork->getNetworkTopology().getInputSize()));
			teacher->addTeachingLesson(new TeachingLessonLinearInput(teachingLessonsPatterns.back(), teachingLessonsInputs.back()));
		}

		for (int i = 0; i < std::min(static_cast<int>(transitionCounter), getOptions().minibatchSize); i++)
		{
			int r = randomGenerator->randInt(0, transitionCounter - 1);

			if (getOptions().calculatorType == CT_GPU)
			{
				tmp.getViennaclValueForEditing() = viennacl::column(transitionStorage.nextStates.getViennaclValueForEditing(), r);
				const Vector<>& output = steadyNetwork->calculateWithoutOutputCopy(tmp, TopologicalOrder());

				static viennacl::ocl::kernel& kernel = getKernel("dqn_learning_rule", "set_teaching_input", "dqn_learning_rule.cl");
				
				viennacl::ocl::enqueue(kernel(
					viennacl::traits::opencl_handle(output.getViennaclValue()),
					viennacl::traits::opencl_handle(teachingLessonsInputs[i]->getValues().getViennaclValueForEditing()),
					viennacl::traits::opencl_handle(teachingLessonsInputs[i]->getEnabled().getViennaclValueForEditing()),
					viennacl::traits::opencl_handle(transitionStorage.rewards.getViennaclValue()),
					viennacl::traits::opencl_handle(transitionStorage.actions.getViennaclValue()),
					viennacl::traits::opencl_handle(transitionStorage.isTerminalState.getViennaclValue()),
					cl_uint(viennacl::traits::size(output.getViennaclValue())),
					cl_uint(r),
					cl_float(getOptions().discountFactor)
				));

				teachingLessonsPatterns[i]->getViennaclValueForEditing() = viennacl::column(transitionStorage.states.getViennaclValue(), r);
			}
			else
			{
				double y = transitionStorage.rewards.getEigenValue()[r];

				if (!transitionStorage.isTerminalState.getEigenValue()[r])
				{
					tmp.getEigenValueForEditing() = transitionStorage.nextStates.getEigenValue().col(r);
					const Vector<>& output = steadyNetwork->calculateWithoutOutputCopy(tmp, TopologicalOrder());

					double q = output.getEigenValue().maxCoeff();
					qAvgSum += q;
					y += getOptions().discountFactor * q;
				}

				teachingLessonsInputs[i]->clear();
				teachingLessonsInputs[i]->set(transitionStorage.actions.getEigenValue()[r], y);

				teachingLessonsPatterns[i]->getEigenValueForEditing() = transitionStorage.states.getEigenValue().col(r);
			}

		}
		teacher->setCalculatorType(getOptions().calculatorType);
		//auto gradient = checkGradient(&teacher, getOptions()->environment->getNeuralNetwork()->getNetworkTopology());

		std::unique_ptr<SupervisedLearningResult> result(static_cast<SupervisedLearningResult*>(gradientDescent->start()));
		currentTotalError += result->totalError;
		static int i = 0;
		if (i++ >= 2000)
		{
			viennacl::backend::finish();
			i = 0;
		}
		
	}

	std::string DQNLearningRule::getName()
	{
		return "DQNLearningRule";
	}

	std::vector<std::string> DQNLearningRule::getDataSetLabels() const
	{
		std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
		labels.push_back(DATA_SET_TRAINING_ERROR);
		labels.push_back(DATA_SET_EPSILON);
		labels.push_back(DATA_SET_Q_VALUE);
		labels.push_back(DATA_SET_AVG_Q_VALUE);
		return labels;
	}


	void DQNLearningRule::doIteration()
	{
		log("Iteration " + std::to_string(learningState->iterations), LL_LOW);

		currentTotalError = 0;
		totalReward.getEigenValueForEditing() = 0;
		bool nextIsStartingState = true;
		double totalQ = 0;
		int totalQValues = 0;
		qAvgSum = 0;

		AbstractNetworkTopology& networkTopology = getOptions().environment->getNeuralNetwork().getNetworkTopology();

		for (int i = 0; i < getOptions().targetNetworkUpdateFrequency; i++) {
			getOptions().environment->doSimulationStep(reward);
			if (getOptions().calculatorType == CT_GPU)
				totalReward.getViennaclValueForEditing() += reward.getViennaclValue();
			else
				totalReward.getEigenValueForEditing() += reward.getEigenValue();

			if (nextIsStartingState)
			{
				std::vector<double> output(getOptions().environment->getNeuralNetwork().getNetworkTopology().getOutputSize());
				getOptions().environment->getNeuralNetwork().getNetworkTopology().getOutput(output);
				totalQ += *max_element(output.begin(), output.end());
				totalQValues++;
				nextIsStartingState = false;
			}

			storeTransition(&networkTopology, reward);

			if (getOptions().calculatorType == CT_CPU && isTerminalState.getEigenValue()) {
				nextIsStartingState = true;
			}

			if (waitUntilLearningStarts > 0)
				waitUntilLearningStarts--;
			else
			{
				doSupervisedLearning();

				double e = getOptions().environment->getEpsilon();
				if (e > getOptions().finalExploration)
					getOptions().environment->setEpsilon(e - (getOptions().initialExploration - getOptions().finalExploration) / getOptions().finalExplorationFrame);
			}
		}

		if (totalQValues > 0)
			learningState->addData(DATA_SET_Q_VALUE, totalQ / totalQValues);

		learningState->addData(DATA_SET_EPSILON, getOptions().environment->getEpsilon());
		learningState->addData(DATA_SET_AVG_Q_VALUE, qAvgSum / getOptions().targetNetworkUpdateFrequency);

		learningState->addData(DATA_SET_REWARD, totalReward.getEigenValue()); 
		log("Reward: " + std::to_string(totalReward.getEigenValue()), LL_LOW);

		learningState->addData(DATA_SET_TRAINING_ERROR, currentTotalError / getOptions().targetNetworkUpdateFrequency);

		steadyNetwork->getNetworkTopology().copyWeightsFrom(getOptions().environment->getNeuralNetwork().getNetworkTopology());

		double e = getOptions().environment->getEpsilon();
		getOptions().environment->setEpsilon(0);
		getOptions().environment->rate();
		getOptions().environment->setEpsilon(e);

	}


	const DQNLearningRuleOptions& DQNLearningRule::getOptions() const
	{
		return static_cast<DQNLearningRuleOptions&>(*options.get());
	}

}
