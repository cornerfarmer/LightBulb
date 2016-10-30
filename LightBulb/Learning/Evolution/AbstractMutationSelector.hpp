#pragma once

#ifndef _ABSTRACTMUTATIONSELECTOR_H_
#define _ABSTRACTMUTATIONSELECTOR_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"
#include "Tools/AbstractCloneable.hpp"

// Library includes
#include <vector>
#include <utility>
#include <map>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;

	//
	class AbstractMutationSelector : public virtual AbstractCloneable, public AbstractRandomGeneratorUser
	{
	private:
		std::vector<AbstractEvolutionObject*> selectedObjects;

		std::map<AbstractEvolutionObject*, int>* currentCounter;
	protected:
		virtual void addObjectToMutate(AbstractEvolutionObject& object);

		virtual void selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) = 0;
	public:
		virtual ~AbstractMutationSelector() {}
		friend void swap(AbstractMutationSelector& lhs, AbstractMutationSelector& rhs) noexcept;

		//
		virtual void executeMutationSelection(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter);

		virtual std::vector<AbstractEvolutionObject*>& getMutationSelection();
	};
}

#endif
