#pragma once

#ifndef _ABSTRACTCOEVOLUTIONFITNESSFUNCTION_H_
#define _ABSTRACTCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes
#include <map>

// Include

namespace LightBulb
{
	// Forward declarations
	class AbstractCoevolutionEnvironment;
	class AbstractIndividual;
	/**
	* \brief Describes the results of a AbstractCombiningStrategy.
	* \details Maps: First individual - Second individual - round number => True, if first individual has won.
	*/
	typedef std::map<AbstractIndividual*, std::map<AbstractIndividual*, std::map<int, bool>>> CombiningStrategyResults;
	/**
	 * \brief Describes a function which calculates fitness values from CombiningStrategyResults.
	 */
	class AbstractCoevolutionFitnessFunction
	{
	protected:
	public:
		virtual ~AbstractCoevolutionFitnessFunction() {};
		/**
		 * \brief Calculate fitness values from the given CombiningStrategyResults.
		 * \param results The combining strategy results.
		 * \return A map which contains fitness values for all individuals.
		 */
		virtual std::map<const AbstractIndividual*, double>* execute(const CombiningStrategyResults& results) = 0;
	};
}

#endif
