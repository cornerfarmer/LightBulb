#ifndef _EVOLUTIONLEARNINGRESULT_H_
#define _EVOLUTIONLEARNINGRESULT_H_

#include "Learning/AbstractLearningResult.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"

namespace LightBulb
{
	struct EvolutionLearningResult : public AbstractLearningResult
	{
		std::vector<std::unique_ptr<AbstractEvolutionObject>> bestObjects;
	};
}


#endif
