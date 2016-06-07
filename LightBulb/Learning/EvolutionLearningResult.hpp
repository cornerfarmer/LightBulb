#ifndef _EVOLUTIONLEARNINGRESULT_H_
#define _EVOLUTIONLEARNINGRESULT_H_

#include "AbstractLearningResult.hpp"
#include "Evolution/AbstractEvolutionObject.hpp"

struct EvolutionLearningResult : public AbstractLearningResult
{
	std::vector<std::unique_ptr<AbstractEvolutionObject>> bestObjects;
};


#endif
