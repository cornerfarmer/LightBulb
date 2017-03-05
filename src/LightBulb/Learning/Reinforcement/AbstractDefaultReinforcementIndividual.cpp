// Includes
#include "LightBulb/Learning/Reinforcement/AbstractDefaultReinforcementIndividual.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"

//Library include

namespace LightBulb
{

	void AbstractDefaultReinforcementIndividual::doNNCalculation()
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
				for (int i = 0; i < lastOutput.getViennaclValue().size(); i++)
				{
					if (useStochasticActionDecision)
					{
						viennacl::ocl::enqueue(setBooleanOutputNonGreedyStochasticKernel->use()(
							viennacl::traits::opencl_handle(lastBooleanOutput.getViennaclValueForEditing()),
							viennacl::traits::opencl_handle(lastOutput.getViennaclValue()),
							cl_uint(i),
							cl_float(randomGenerator->randFloat())
						));
					}
					else
					{
						viennacl::ocl::enqueue(setBooleanOutputNonGreedyKernel->use()(
							viennacl::traits::opencl_handle(lastBooleanOutput.getViennaclValueForEditing()),
							viennacl::traits::opencl_handle(lastOutput.getViennaclValue()),
							cl_uint(i)
						));
					}
				}
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
					viennacl::ocl::enqueue(setBooleanOutputRandKernel->use()(
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
					viennacl::ocl::enqueue(setBooleanOutputBestKernel->use()(
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

		// Interpret the output
		interpretNNOutput(lastBooleanOutput);
	}
	
	AbstractDefaultReinforcementIndividual::~AbstractDefaultReinforcementIndividual() = default;

	AbstractDefaultReinforcementIndividual::AbstractDefaultReinforcementIndividual(AbstractReinforcementEnvironment* environment_, const FeedForwardNetworkTopologyOptions& options, bool epsilonGreedly_, double epsilon_)
	{
		environment = environment_;
		buildNeuralNetwork(options);
		epsilonGreedly = epsilonGreedly_;
		epsilon = epsilon_;
		useStochasticActionDecision = true;
		initializeKernels();
	}

	AbstractDefaultReinforcementIndividual::AbstractDefaultReinforcementIndividual()
	{
		initializeKernels();
	}

	void AbstractDefaultReinforcementIndividual::initializeKernels()
	{
		setBooleanOutputNonGreedyKernel.reset(new Kernel("reinforcement_environment", "set_boolean_output_non_greedy"));
		setBooleanOutputNonGreedyStochasticKernel.reset(new Kernel("reinforcement_environment", "set_boolean_output_non_greedy_stochastic"));
		setBooleanOutputRandKernel.reset(new Kernel("reinforcement_environment", "set_boolean_output_rand"));
		setBooleanOutputBestKernel.reset(new Kernel("reinforcement_environment", "set_boolean_output_best"));
	}

	void AbstractDefaultReinforcementIndividual::initializeForLearning()
	{
		// Randomize all weights
		neuralNetwork->getNetworkTopology().randomizeDependingOnLayerSize(*randomGenerator);		
	}

	NeuralNetwork& AbstractDefaultReinforcementIndividual::getNeuralNetwork()
	{
		return *neuralNetwork.get();
	}

	double AbstractDefaultReinforcementIndividual::getEpsilon()
	{
		return epsilon;
	}


	void AbstractDefaultReinforcementIndividual::setEpsilon(double newEpsilon)
	{
		epsilon = newEpsilon;
	}
	
	void AbstractDefaultReinforcementIndividual::buildNeuralNetwork(const FeedForwardNetworkTopologyOptions& options)
	{
		// Create a new network topology from the adjusted options.
		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);

		// Create a neural network from the network topolgy
		neuralNetwork.reset(new NeuralNetwork(networkTopology));

		lastInput.getEigenValueForEditing().resize(networkTopology->getInputSize());

		// Initialize the mutation strength vector
		buildOutputBuffer();
	}


	void AbstractDefaultReinforcementIndividual::buildOutputBuffer()
	{
		lastBooleanOutput.getEigenValueForEditing().resize(neuralNetwork->getNetworkTopology().getOutputSize());
	}


	const Vector<char>& AbstractDefaultReinforcementIndividual::getLastBooleanOutput() const
	{
		return lastBooleanOutput;
	}

	const Vector<>& AbstractDefaultReinforcementIndividual::getLastInput() const
	{
		return lastInput;
	}

	void AbstractDefaultReinforcementIndividual::setStochasticActionDecision(bool useStochasticActionDecision_)
	{
		useStochasticActionDecision = useStochasticActionDecision_;
	}

	void AbstractDefaultReinforcementIndividual::setCalculatorType(const CalculatorType& calculatorType)
	{
		AbstractLinearAlgebraUser::setCalculatorType(calculatorType);
		neuralNetwork->getNetworkTopology().setCalculatorType(calculatorType);
	}
}
