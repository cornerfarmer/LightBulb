#pragma once

#ifndef _ABSTRACTREUSESELECTOR_H_
#define _ABSTRACTREUSESELECTOR_H_

// Includes
#include "Tools/AbstractCloneable.hpp"

// Library includes
#include <vector>
#include <utility>
#include <map>
#include <string>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;

	//
	class AbstractReuseSelector : public virtual AbstractCloneable
	{
	private:
		std::vector<AbstractEvolutionObject*> selectedObjects;

		std::map<AbstractEvolutionObject*, int>* currentCounter;
	protected:
		virtual void addObjectToReuse(AbstractEvolutionObject& object);

		virtual void selectForReuse(int reuseCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) = 0;
	public:
		virtual ~AbstractReuseSelector() {};
		//
		virtual void executeReuseSelection(int reuseCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter);

		virtual const std::vector<AbstractEvolutionObject*>& getReuseSelection() const;
	};
}

#endif
