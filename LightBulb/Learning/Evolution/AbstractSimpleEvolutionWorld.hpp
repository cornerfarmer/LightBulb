#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONWORLD_H_
#define _ABSTRACTSIMPLEEVOLUTIONWORLD_H_

// Library Includes
#include <vector>

// Include
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class AbstractEvolutionObject;

	// This class is simplification of the AbstractEvolutionWorld class.
	// It decreases the work you have to do for your world, but also decreases your possibilities.
	// Nevertheless this class can be used in the most of all cases.
	class AbstractSimpleEvolutionWorld : public AbstractEvolutionWorld
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractSimpleEvolutionWorld const& world);
		template <class Archive>
		friend void load(Archive& archive, AbstractSimpleEvolutionWorld& world);
	protected:
		// A vector which holds all current evolution objects
		std::vector<AbstractEvolutionObject*> objects;
		// This method should (only) create new evolution object
		virtual AbstractEvolutionObject* createNewObject() = 0;
		// This method can be used to do some extra work, when the world resets.
		virtual void resetWorld() {};
	public:
		AbstractSimpleEvolutionWorld();
		// Inherited:
		AbstractEvolutionObject& addNewObject(bool addToWorld = true) override;
		std::vector<AbstractEvolutionObject*>& getEvolutionObjects() override;
		void setEvolutionObjects(const std::vector<AbstractEvolutionObject*>& newObjects) override;
		void reset() override;
		int getPopulationSize() const override;
		void clearPopulation() override;
		void releaseAllObjects() override;
		void addExistingObject(AbstractEvolutionObject* newObject) override;
	};
}

#include "IO/AbstractSimpleEvolutionWorldIO.hpp"

#endif
