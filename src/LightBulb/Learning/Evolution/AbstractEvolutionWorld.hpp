#pragma once

#ifndef _ABSTRACTEVOLUTIONWORLD_H_
#define _ABSTRACTEVOLUTIONWORLD_H_

// Library Includes
#include <vector>
#include <memory>

// Includes
#include <Logging/AbstractLoggable.hpp>
#include <Learning/LearningState.hpp>
#include "IO/UseParentSerialization.hpp"
#include "Random/AbstractRandomGeneratorUser.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class AbstractEvolutionObject;

	typedef std::vector<std::pair<double, AbstractEvolutionObject*>> Highscore;

	// This class should describe a world which contains multiple evolution objects.
	// The evolution world has to simulate the environment which surrounds its evolution objects.
	class AbstractEvolutionWorld : public AbstractLoggable, public AbstractRandomGeneratorUser
	{
	private:
		Highscore currentHighscore;
		bool recalculateHighscore;
	protected:
		LearningState* learningState;
	public:
		virtual ~AbstractEvolutionWorld() {}

		AbstractEvolutionWorld();

		virtual std::vector<AbstractEvolutionObject*>& getEvolutionObjects() = 0;
		virtual void setEvolutionObjects(const std::vector<AbstractEvolutionObject*>& newObjects) = 0;
		// This method should create a new evolution object and add it to the world
		virtual AbstractEvolutionObject* addNewObject(bool addToWorld = true) = 0;
		// This method should execute one simulation step.
		// After each simulation step the evolution learning rule will execute each evolution command (selection, mutation, recombination...)
		virtual bool doSimulationStep() = 0;
		// Returns a list of all current evolution objects ordered by their score
		virtual Highscore& getHighscoreList();
		// This method should calculate the score of the given evolution object
		virtual double getScore(const AbstractEvolutionObject& object) const = 0;
		//
		virtual double getRealScore(const AbstractEvolutionObject& object) const { return getScore(object); }
		virtual void initializeForLearning() {}

		virtual void releaseAllObjects() = 0;
		// Reset the whole world (This method can for instance reset the environment or the current evolution objects...)
		virtual void reset() = 0;

		virtual std::vector<std::string> getDataSetLabels() const;

		void setLearningState(LearningState& learningState_);

		virtual int getPopulationSize() const = 0;

		virtual void clearPopulation() = 0;

		virtual void addExistingObject(AbstractEvolutionObject* newObject) = 0;

		void refreshHighscore();
	};
}

EMPTY_SERIALIZATION(LightBulb::AbstractEvolutionWorld, LightBulb);

#endif