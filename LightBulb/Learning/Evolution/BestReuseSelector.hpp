#pragma once

#ifndef _BESTREUSESELECTOR_H_
#define _BESTREUSESELECTOR_H_

// Library includes
#include <vector>
#include <utility>
#include <map>

// Includes
#include "AbstractReuseSelector.hpp"

// Forward declarations
class AbstractEvolutionObject;

//
class BestReuseSelector : public AbstractReuseSelector
{
private:
protected:
	void selectForReuse(int reuseCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
public:
};

#endif
