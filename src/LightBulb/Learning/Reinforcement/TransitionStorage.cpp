// Includes
#include "LightBulb/Learning/Reinforcement/TransitionStorage.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementIndividual.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"

// Library includes

namespace LightBulb
{
	TransitionStorage::TransitionStorage()
	{
		determineActionKernel.reset(new Kernel("dqn_learning_rule", "determine_action"));
	}
	
	TransitionStorage::~TransitionStorage() = default;

	void TransitionStorage::reset(int maxRecordNumber, int networkInputSize, bool replaceStoredTransitions_)
	{
		memorySize = maxRecordNumber;
		replaceStoredTransitions = replaceStoredTransitions_;
		states.getEigenValueForEditing().resize(networkInputSize, maxRecordNumber);
		nextStates.getEigenValueForEditing().resize(networkInputSize, maxRecordNumber);
		actions.getEigenValueForEditing().resize(maxRecordNumber);
		isTerminalState.getEigenValueForEditing().resize(maxRecordNumber);
		rewards.getEigenValueForEditing().resize(maxRecordNumber);
		inputTemp.getEigenValueForEditing().resize(networkInputSize);
		nextTransitionIndex = 0;
		transitionCounter = 0;
	}

	void TransitionStorage::storeTransition(const AbstractReinforcementIndividual& individual, const AbstractReinforcementEnvironment& environment, const Scalar<>& reward)
	{
		if (transitionCounter < memorySize || replaceStoredTransitions)
		{
			int index = nextTransitionIndex++;
			nextTransitionIndex %= memorySize;
			if (transitionCounter < memorySize)
				transitionCounter++;

			if (isCalculatorType(CT_GPU))
			{
				copyVectorToMatrixCol(states.getViennaclValueForEditing(), individual.getLastInput().getViennaclValue(), index);

				environment.isTerminalState(isTerminalStateTmp);
				copyScalarToVectorElement(isTerminalState.getViennaclValueForEditing(), isTerminalStateTmp.getViennaclValue(), index);

				environment.getNNInput(inputTemp);
				copyVectorToMatrixCol(nextStates.getViennaclValueForEditing(), inputTemp.getViennaclValue(), index);

				copyScalarToVectorElement(rewards.getViennaclValueForEditing(), reward.getViennaclValue(), index);

				viennacl::ocl::enqueue(determineActionKernel->use()(
					viennacl::traits::opencl_handle(individual.getLastBooleanOutput().getViennaclValue()),
					viennacl::traits::opencl_handle(actions.getViennaclValueForEditing()),
					cl_uint(viennacl::traits::size(individual.getLastBooleanOutput().getViennaclValue())),
					cl_uint(index)
					));

			}
			else
			{
				states.getEigenValueForEditing().col(index) = individual.getLastInput().getEigenValue();

				environment.isTerminalState(isTerminalStateTmp);
				isTerminalState.getEigenValueForEditing()[index] = isTerminalStateTmp.getEigenValue();

				if (!isTerminalStateTmp.getEigenValue()) {
					environment.getNNInput(inputTemp);
					nextStates.getEigenValueForEditing().col(index) = inputTemp.getEigenValue();
				}

				rewards.getEigenValueForEditing()(index) = reward.getEigenValue();

				for (int i = 0; i < individual.getLastBooleanOutput().getEigenValue().size(); i++)
				{
					if (individual.getLastBooleanOutput().getEigenValue()[i])
					{
						actions.getEigenValueForEditing()(index) = i;
						break;
					}
				}
			}
		}
	}

	int TransitionStorage::getTransitionCounter() const
	{
		return transitionCounter;
	}

	const Matrix<>& TransitionStorage::getStates() const
	{
		return states;
	}

	const Vector<int>& TransitionStorage::getActions() const
	{
		return actions;
	}

	const Vector<char>& TransitionStorage::getIsTerminalState() const
	{
		return isTerminalState;
	}

	const Matrix<>& TransitionStorage::getNextStates() const
	{
		return nextStates;
	}

	const Vector<>& TransitionStorage::getRewards() const
	{
		return rewards;
	}
}
