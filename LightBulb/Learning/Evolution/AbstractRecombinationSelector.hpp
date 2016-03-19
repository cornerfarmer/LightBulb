#pragma once

#ifndef _ABSTRACTRECOMBINATIONSELECTOR_H_
#define _ABSTRACTRECOMBINATIONSELECTOR_H_

// Library includes
#include <vector>
#include <utility>
#include <array>
#include <map>
#include <string>

// Forward declarations
class AbstractEvolutionObject;

//
class AbstractRecombinationSelector
{
private:
	std::vector<AbstractEvolutionObject*> selectedObjects;

	std::map<AbstractEvolutionObject*, int>* currentCounter;
protected:
	virtual void addObjectToRecombination(AbstractEvolutionObject* object);

	virtual void selectForRecombination(int recombinationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) = 0;
public:
	virtual ~AbstractRecombinationSelector() {};
	//
	virtual void executeRecombinationSelection(int recombinationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, int>* counter);

	virtual std::vector<AbstractEvolutionObject*>* getRecombinationSelection();
};

#endif
