#ifndef _EVOLUTIONLEARNINGRESULT_H_
#define _EVOLUTIONLEARNINGRESULT_H_

#include "Learning/AbstractLearningResult.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes the learning result of an evolution learning rule.
	 */
	struct EvolutionLearningResult : public AbstractLearningResult
	{
		/**
		 * \brief A vector of the best individuals that were produced by the evolution learning rule.
		 */
		std::vector<std::unique_ptr<AbstractIndividual>> bestIndividuals;
	};
}


#endif
