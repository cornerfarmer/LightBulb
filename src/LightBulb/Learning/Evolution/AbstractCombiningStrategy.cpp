// Includes
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

namespace LightBulb
{
	void CombiningStrategyResults::reset(int totalMatches)
	{
		nextResultIndex = 0;
		if (resultVector.getEigenValue().size() < totalMatches * 2)
			resultVector.getEigenValueForEditing().resize(totalMatches * 2);
		matchIndices.clear();
	}

	AbstractCombiningStrategy::AbstractCombiningStrategy(AbstractCoevolutionEnvironment* secondEnvironment_)
	{
		results.reset(new CombiningStrategyResults());
		secondEnvironment = secondEnvironment_;
	}

	void AbstractCombiningStrategy::setResult(AbstractIndividual& firstPlayer, AbstractIndividual& secondPlayer, int round, const Scalar<bool>& firstPlayerHasWon)
	{
		if (isCalculatorType(CT_GPU))
		{
			static viennacl::ocl::kernel& kernel = getKernel("combining_strategy", "set_results", "combining_strategy.cl");

			viennacl::ocl::enqueue(kernel(
				viennacl::traits::opencl_handle(results->resultVector.getViennaclValueForEditing()),
				cl_uint(results->nextResultIndex),
				viennacl::traits::opencl_handle(firstPlayerHasWon.getViennaclValue())
			));
		}
		else
		{
			results->resultVector.getEigenValueForEditing()(results->nextResultIndex) = firstPlayerHasWon.getEigenValue();
			results->resultVector.getEigenValueForEditing()(results->nextResultIndex + 1) = !firstPlayerHasWon.getEigenValue();

			firstPlayerWins += firstPlayerHasWon.getEigenValue();
		}
		results->matchIndices[&firstPlayer][&secondPlayer][round] = results->nextResultIndex++;
		results->matchIndices[&secondPlayer][&firstPlayer][round] = results->nextResultIndex++;
	}

	CombiningStrategyResults& AbstractCombiningStrategy::execute(AbstractCoevolutionEnvironment& environment)
	{
		results->reset(getTotalMatches(environment));
		firstPlayerWins = 0;

		combine(environment, environment.getIndividuals(), secondEnvironment ? secondEnvironment->getIndividuals() : environment.getIndividuals());

		return *results.get();
	}

	void AbstractCombiningStrategy::setSecondEnvironment(AbstractCoevolutionEnvironment& newSecondEnvironment)
	{
		secondEnvironment = &newSecondEnvironment;
	}

	const CombiningStrategyResults& AbstractCombiningStrategy::getPrevResults() const
	{
		return *results.get();
	}

	int AbstractCombiningStrategy::getFirstPlayerWins() const
	{
		return firstPlayerWins;
	}
}
