#pragma once

#ifndef _ABSTRACTMUTATIONSELECTOR_H_
#define _ABSTRACTMUTATIONSELECTOR_H_

// Library includes
#include <vector>
#include <utility>
#include <map>
#include <string>

// Forward declarations
class AbstractEvolutionObject;

//
class AbstractMutationSelector
{
private:
	std::vector<AbstractEvolutionObject*> selectedObjects;

	std::map<AbstractEvolutionObject*, int>* currentCounter;
protected:
	virtual void addObjectToMutate(AbstractEvolutionObject* object);

	virtual void selectForMutation(int mutationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) = 0;
public:
	virtual ~AbstractMutationSelector() {};
	//
	virtual void executeMutationSelection(int mutationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, int>* counter);

	virtual std::vector<AbstractEvolutionObject*>* getMutationSelection();
};

#endif
