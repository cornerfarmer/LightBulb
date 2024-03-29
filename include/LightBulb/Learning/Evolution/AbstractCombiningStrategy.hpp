#pragma once

#ifndef _ABSTRACTCOMBININGSTRATEGY_H_
#define _ABSTRACTCOMBININGSTRATEGY_H_

// Include
#include "LightBulb/Random/AbstractRandomGeneratorUser.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"

// Library Includes
#include <vector>
#include <memory>
#include <map>

namespace LightBulb
{
	// Forward declarations
	class AbstractCoevolutionEnvironment;
	class AbstractIndividual;
	class Kernel;
	struct CombiningStrategyResults
	{
		Vector<char> resultVector;
		std::map<AbstractIndividual*, std::map<AbstractIndividual*, std::map<int, int>>> matchIndices;
		int nextResultIndex;

		void reset(int totalMatches);
	};
	/**
	 * \brief Describes a strategy for combining individual from one or two coevolution environments.
	 * \details The strategy compares each two individuals and stores the results in a CombiningStrategyResults object.
	 */
	class AbstractCombiningStrategy : public virtual AbstractRandomGeneratorUser, public virtual AbstractLinearAlgebraUser
	{
	private:
		/**
		 * \brief Stores the current combining results.
		 */
		std::unique_ptr<CombiningStrategyResults> results;
		std::unique_ptr<Kernel> setResultsKernel;
		/**
		 * \brief Counts how often the first player has won.
		 */
		int firstPlayerWins;
	protected:
		Scalar<bool> firstPlayerHasWon;
		/**
		 * \brief Contains a second environment, if one is used.
		 */
		AbstractCoevolutionEnvironment* secondEnvironment;
		/**
		 * \brief Does the combining.
		 * \param simulationEnvironment The environment which should be used for comparing individuals.
		 * \param firstIndividuals The first pool of individuals.
		 * \param secondIndividuals The second pool of individuals.
		 * \note If only one environment is used, the first and second pool will be the same.
		 */
		virtual void combine(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals) = 0;
		/**
		 * \brief Registers the result of one combination.
		 * \param firstPlayer The first player which has been used.
		 * \param secondPlayer The second player which has been used.
		 * \param round The round number.
		 * \param firstPlayerHasWon True, if the first player has won.
		 */
		void setResult(AbstractIndividual& firstPlayer, AbstractIndividual& secondPlayer, int round, const Scalar<bool>& firstPlayerHasWon);
	public:
		/**
		 * \brief Creates the combining strategy.
		 * \param secondEnvironment_ Optional a second environment whose individuals should be used beside the individuals from the default environment.
		 */
		AbstractCombiningStrategy(AbstractCoevolutionEnvironment* secondEnvironment_ = nullptr);
		~AbstractCombiningStrategy();
		/**
		 * \brief Executes combining of individuals from the given environment.
		 * \param environment The environment whose individuals should be used.
		 * \return The combining results.
		 */
		virtual CombiningStrategyResults& execute(AbstractCoevolutionEnvironment& environment);
		/**
		 * \brief Sets a second environment whose individuals should be used beside the individuals from the default environment.
		 * \param newSecondEnvironment The environment to use.
		 */
		virtual void setSecondEnvironment(AbstractCoevolutionEnvironment& newSecondEnvironment);
		/**
		 * \brief Returns the combining results of the last calculation.
		 * \return The combining results.
		 */
		virtual const CombiningStrategyResults& getPrevResults() const;
		/**
		 * \brief Returns how often the first player has won in the last calculation.
		 * \return The amount of first player victories.
		 */
		virtual int getFirstPlayerWins() const;
		/**
		 * \brief Returns the total amount of matches in one calculation.
		 * \param simulationEnvironment The environment which should be used for calculation.
		 * \return The total amount of matches.
		 */
		virtual int getTotalMatches(const AbstractCoevolutionEnvironment& simulationEnvironment) const = 0;
	};
}

#endif
