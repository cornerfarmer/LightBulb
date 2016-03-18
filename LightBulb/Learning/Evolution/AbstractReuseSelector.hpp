#pragma once

#ifndef _ABSTRACTREUSESELECTOR_H_
#define _ABSTRACTREUSESELECTOR_H_

// Library includes
#include <vector>
#include <utility>
#include <map>
#include <string>

// Forward declarations
class AbstractEvolutionObject;

//
class AbstractReuseSelector
{
private:
	std::vector<AbstractEvolutionObject*> selectedObjects;

	std::map<AbstractEvolutionObject*, std::map<std::string, int>>* currentCounter;
protected:
	void addObjectToReuse(AbstractEvolutionObject* object);

	virtual void selectForReuse(int reuseCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore) = 0;
public:
	virtual ~AbstractReuseSelector() {};
	//
	void executeReuseSelection(int reuseCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter);

	std::vector<AbstractEvolutionObject*>* getReuseSelection();
};

#endif
