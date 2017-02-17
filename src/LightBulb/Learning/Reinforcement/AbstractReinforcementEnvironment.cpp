// Includes
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

//Library include

namespace LightBulb
{
	void AbstractReinforcementEnvironment::doNNCalculation()
	{
		neuralNetwork->getNetworkTopology().resetActivation();
		// Get the input
		getNNInput(lastInput);		

		TopologicalOrder topologicalOrder;
		// Calculate the output from the the input
		const Vector<>& lastOutput = neuralNetwork->calculateWithoutOutputCopy(lastInput, topologicalOrder, false);

		if (!epsilonGreedly) {
			if (isCalculatorType(CT_GPU))
			{
				throw std::logic_error("Not implemented");
			}
			else
			{
				for (int i = 0; i < lastOutput.getEigenValue().size(); i++)
				{
					if (useStochasticActionDecision)
						lastBooleanOutput.getEigenValueForEditing()[i] = (randomGenerator->randFloat() < lastOutput.getEigenValue()[i]);
					else
						lastBooleanOutput.getEigenValueForEditing()[i] = (0.5 < lastOutput.getEigenValue()[i]);
				}
			}
		}
		else
		{
			if (randomGenerator->randFloat() < epsilon)
			{
				if (isCalculatorType(CT_GPU))
				{
					static viennacl::ocl::kernel& kernel = getKernel("reinforcement_environment", "set_boolean_output_rand", "reinforcement_environment.cl");

					viennacl::ocl::enqueue(kernel(
						viennacl::traits::opencl_handle(lastBooleanOutput.getViennaclValueForEditing()),
						cl_uint(viennacl::traits::size(lastBooleanOutput.getViennaclValue())),
						cl_uint(randomGenerator->randInt(0, lastBooleanOutput.getViennaclValue().size() - 1))
					));
				}
				else
				{
					lastBooleanOutput.getEigenValueForEditing().setZero();
					lastBooleanOutput.getEigenValueForEditing()[randomGenerator->randInt(0, lastBooleanOutput.getEigenValue().size() - 1)] = true;
				}
			}
			else
			{
				if (isCalculatorType(CT_GPU))
				{
					static viennacl::ocl::kernel& kernel = getKernel("reinforcement_environment", "set_boolean_output_best", "reinforcement_environment.cl");

					viennacl::ocl::enqueue(kernel(
						viennacl::traits::opencl_handle(lastBooleanOutput.getViennaclValueForEditing()),
						viennacl::traits::opencl_handle(lastOutput.getViennaclValue()),
						cl_uint(viennacl::traits::size(lastBooleanOutput.getViennaclValue()))
					));
				}
				else
				{
					lastBooleanOutput.getEigenValueForEditing().setZero();
					int bestOutput = 0;
					for (int i = 1; i < lastOutput.getEigenValue().size(); i++)
					{
						if (lastOutput.getEigenValue()[bestOutput] <= lastOutput.getEigenValue()[i])
							bestOutput = i;
					}
					lastBooleanOutput.getEigenValueForEditing()[bestOutput] = true;
				}
			}
		}
		lastOutput.getEigenValue();

		// Interpret the output
		interpretNNOutput(lastBooleanOutput);
	}

	AbstractReinforcementEnvironment::~AbstractReinforcementEnvironment() = default;

	AbstractReinforcementEnvironment::AbstractReinforcementEnvironment(FeedForwardNetworkTopologyOptions& options, bool epsilonGreedly_, double epsilon_)
	{
		buildNeuralNetwork(options);
		epsilonGreedly = epsilonGreedly_;
		epsilon = epsilon_;
		useStochasticActionDecision = true;
	}

	AbstractReinforcementEnvironment::AbstractReinforcementEnvironment() = default;

	void AbstractReinforcementEnvironment::initializeForLearning()
	{
		// Randomize all weights
		neuralNetwork->getNetworkTopology().randomizeDependingOnLayerSize(*randomGenerator);		
	}

	NeuralNetwork& AbstractReinforcementEnvironment::getNeuralNetwork()
	{
		return *neuralNetwork.get();
	}

	double AbstractReinforcementEnvironment::getEpsilon()
	{
		return epsilon;
	}


	void AbstractReinforcementEnvironment::setEpsilon(double newEpsilon)
	{
		epsilon = newEpsilon;
	}

	void AbstractReinforcementEnvironment::setLearningState(LearningState& learningState_)
	{
		learningState = &learningState_;
	}

	void AbstractReinforcementEnvironment::buildNeuralNetwork(FeedForwardNetworkTopologyOptions& options)
	{
		// Create a new network topology from the adjusted options.
		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);

		// Create a neural network from the network topolgy
		neuralNetwork.reset(new NeuralNetwork(networkTopology));

		lastInput.getEigenValueForEditing().resize(networkTopology->getInputSize());

		// Initialize the mutation strength vector
		buildOutputBuffer();
	}


	void AbstractReinforcementEnvironment::buildOutputBuffer()
	{
		lastBooleanOutput.getEigenValueForEditing().resize(neuralNetwork->getNetworkTopology().getOutputSize());
	}

	std::vector<std::string> AbstractReinforcementEnvironment::getDataSetLabels() const
	{
		std::vector<std::string> labels;
		return labels;
	}

	const Vector<char>& AbstractReinforcementEnvironment::getLastBooleanOutput() const
	{
		return lastBooleanOutput;
	}

	const Vector<>& AbstractReinforcementEnvironment::getLastInput() const
	{
		return lastInput;
	}

	void AbstractReinforcementEnvironment::setStochasticActionDecision(bool useStochasticActionDecision_)
	{
		useStochasticActionDecision = useStochasticActionDecision_;
	}

	void AbstractReinforcementEnvironment::setCalculatorType(const CalculatorType& calculatorType)
	{
		AbstractLinearAlgebraUser::setCalculatorType(calculatorType);
		neuralNetwork->getNetworkTopology().setCalculatorType(calculatorType);
	}
}
