#pragma once

#ifndef _EVOLUTIONOBJECTINTERFACE_H_
#define _EVOLUTIONOBJECTINTERFACE_H_

// Library Includes


// Forward declarations
class EvolutionLearningRule;


class EvolutionObjectInterface 
{
protected:
	
public:	
	virtual void doNNCalculation(EvolutionLearningRule& learningRule) = 0;
	virtual ~EvolutionObjectInterface() {};
};
#endif