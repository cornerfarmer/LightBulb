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
#include "LightBulb/LinearAlgebra/Kernel.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementIndividual.hpp"

// Library includes

namespace LightBulb
{

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
		options->gradientDescentOptions.neuralNetwork = &getOptions().individual->getNeuralNetwork();
		options->gradientDescentOptions.logger = nullptr;
		options->gradientDescentOptions.calculatorType = getOptions().calculatorType;
		gradientDescent.reset(new GradientDescentLearningRule(options->gradientDescentOptions));
		transitionStorage.reset(new TransitionStorage());

		getOptions().environment->setCalculatorType(getOptions().calculatorType);
		steadyNetwork.reset(getOptions().individual->getNeuralNetwork().clone());

		setTeachingInputKernel.reset(new Kernel("dqn_learning_rule", "set_teaching_input"));
	}

	void DQNLearningRule::initializeTry()
	{
		transitionStorage->reset(getOptions().replayMemorySize, getOptions().individual->getNeuralNetwork().getNetworkTopology().getInputSize(), getOptions().replaceStoredTransitions);
		tmp.getEigenValueForEditing().resize(getOptions().individual->getNeuralNetwork().getNetworkTopology().getInputSize());

		getOptions().environment->setLearningState(*learningState.get());
		getOptions().environment->initializeForLearning();
		getOptions().individual->initializeForLearning();
		steadyNetwork->getNetworkTopology().copyWeightsFrom(getOptions().individual->getNeuralNetwork().getNetworkTopology());
		
		waitUntilLearningStarts = getOptions().replayStartSize;
		getOptions().individual->setEpsilon(getOptions().initialExploration);
	}
	
	void DQNLearningRule::doSupervisedLearning()
	{
		while (teachingLessonsInputs.size() < std::min(static_cast<int>(transitionStorage->getTransitionCounter()), getOptions().minibatchSize))
		{
			teachingLessonsInputs.push_back(new TeachingInput<>(steadyNetwork->getNetworkTopology().getOutputSize()));
			teachingLessonsPatterns.push_back(new Vector<>(steadyNetwork->getNetworkTopology().getInputSize()));
			teacher->addTeachingLesson(new TeachingLessonLinearInput(teachingLessonsPatterns.back(), teachingLessonsInputs.back()));
		}

		for (int i = 0; i < std::min(static_cast<int>(transitionStorage->getTransitionCounter()), getOptions().minibatchSize); i++)
		{
			int r = randomGenerator->randInt(0, transitionStorage->getTransitionCounter() - 1);

			if (getOptions().calculatorType == CT_GPU)
			{
				tmp.getViennaclValueForEditing() = viennacl::column(transitionStorage->getNextStates().getViennaclValue(), r);
				const Vector<>& output = steadyNetwork->calculateWithoutOutputCopy(tmp, TopologicalOrder());
				
				viennacl::ocl::enqueue(setTeachingInputKernel->use()(
					viennacl::traits::opencl_handle(output.getViennaclValue()),
					viennacl::traits::opencl_handle(teachingLessonsInputs[i]->getValues().getViennaclValueForEditing()),
					viennacl::traits::opencl_handle(teachingLessonsInputs[i]->getEnabled().getViennaclValueForEditing()),
					viennacl::traits::opencl_handle(transitionStorage->getRewards().getViennaclValue()),
					viennacl::traits::opencl_handle(transitionStorage->getActions().getViennaclValue()),
					viennacl::traits::opencl_handle(transitionStorage->getIsTerminalState().getViennaclValue()),
					cl_uint(viennacl::traits::size(output.getViennaclValue())),
					cl_uint(r),
					cl_float(getOptions().discountFactor)
				));

				teachingLessonsPatterns[i]->getViennaclValueForEditing() = viennacl::column(transitionStorage->getStates().getViennaclValue(), r);
			}
			else
			{
				double y = transitionStorage->getRewards().getEigenValue()[r];

				if (!transitionStorage->getIsTerminalState().getEigenValue()[r])
				{
					tmp.getEigenValueForEditing() = transitionStorage->getNextStates().getEigenValue().col(r);
					const Vector<>& output = steadyNetwork->calculateWithoutOutputCopy(tmp, TopologicalOrder());

					double q = output.getEigenValue().maxCoeff();
					qAvgSum += q;
					y += getOptions().discountFactor * q;
				}

				teachingLessonsInputs[i]->clear();
				teachingLessonsInputs[i]->set(transitionStorage->getActions().getEigenValue()[r], y);

				teachingLessonsPatterns[i]->getEigenValueForEditing() = transitionStorage->getStates().getEigenValue().col(r);
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

	void DQNLearningRule::setTransitionStorage(const std::shared_ptr<TransitionStorage>& transitionStorage_)
	{
		transitionStorage = transitionStorage_;
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


	void DQNLearningRule::refreshSteadyNetwork()
	{
		steadyNetwork->getNetworkTopology().copyWeightsFrom(getOptions().individual->getNeuralNetwork().getNetworkTopology());
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

		AbstractNetworkTopology& networkTopology = getOptions().individual->getNeuralNetwork().getNetworkTopology();

		for (int i = 0; i < getOptions().targetNetworkUpdateFrequency; i++) {
			getOptions().environment->prepareSimulationStep();
			getOptions().individual->doSimulationStep();
			getOptions().environment->doSimulationStep();
			getOptions().individual->getReward(reward);

			if (getOptions().calculatorType == CT_GPU)
				totalReward.getViennaclValueForEditing() += reward.getViennaclValue();
			else
				totalReward.getEigenValueForEditing() += reward.getEigenValue();

			if (nextIsStartingState)
			{
				std::vector<double> output(getOptions().individual->getNeuralNetwork().getNetworkTopology().getOutputSize());
				getOptions().individual->getNeuralNetwork().getNetworkTopology().getOutput(output);
				totalQ += *max_element(output.begin(), output.end());
				totalQValues++;
				nextIsStartingState = false;
			}

			transitionStorage->storeTransition(*getOptions().individual, *getOptions().environment, reward);

			/*if (getOptions().calculatorType == CT_CPU && isTerminalState.getEigenValue()) {
				nextIsStartingState = true;
			}*/

			if (waitUntilLearningStarts > 0)
				waitUntilLearningStarts--;
			else
			{
				doSupervisedLearning();

				double e = getOptions().individual->getEpsilon();
				if (e > getOptions().finalExploration)
					getOptions().individual->setEpsilon(e - (getOptions().initialExploration - getOptions().finalExploration) / getOptions().finalExplorationFrame);
			}
		}

		if (totalQValues > 0)
			learningState->addData(DATA_SET_Q_VALUE, totalQ / totalQValues);

		learningState->addData(DATA_SET_EPSILON, getOptions().individual->getEpsilon());
		learningState->addData(DATA_SET_AVG_Q_VALUE, qAvgSum / getOptions().targetNetworkUpdateFrequency);

		learningState->addData(DATA_SET_REWARD, totalReward.getEigenValue()); 
		log("Reward: " + std::to_string(totalReward.getEigenValue()), LL_LOW);

		learningState->addData(DATA_SET_TRAINING_ERROR, currentTotalError / getOptions().targetNetworkUpdateFrequency);

		refreshSteadyNetwork();

		double e = getOptions().individual->getEpsilon();
		getOptions().individual->setEpsilon(0);
		getOptions().individual->rate();
		getOptions().individual->setEpsilon(e);

	}


	const DQNLearningRuleOptions& DQNLearningRule::getOptions() const
	{
		return static_cast<DQNLearningRuleOptions&>(*options.get());
	}

}
