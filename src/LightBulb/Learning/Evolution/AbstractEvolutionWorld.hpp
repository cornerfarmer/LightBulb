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
	/**
	 * \brief Describes a ranked list of all evolution objects depending on their fitness values.
	 */
	typedef std::vector<std::pair<double, AbstractEvolutionObject*>> Highscore;
	/**
	 * \brief This class describes a world which contains multiple evolution objects.
	 * \details The evolution world has to simulate the environment which surrounds its evolution objects.
	 */
	class AbstractEvolutionWorld : public AbstractLoggable, public virtual AbstractRandomGeneratorUser
	{
	private:
		/**
		 * \brief The current highscore which ranks all evolution objects by their current fitness value.
		 */
		Highscore currentHighscore;
		/**
		 * \brief True, if the highscore should be recalculated.
		 */
		bool recalculateHighscore;
	protected:
		/**
		 * \brief A pointer to the learning state used by the corresponding learning rule.
		 */
		LearningState* learningState;
	public:
		virtual ~AbstractEvolutionWorld() {}
		/**
		 * \brief Creates a evolution world.
		 */
		AbstractEvolutionWorld();
		/**
		 * \brief Returns all current evolution objects.
		 * \return A vector of evolution objects.
		 */
		virtual std::vector<AbstractEvolutionObject*>& getEvolutionObjects() = 0;
		/**
		 * \brief Sets all evolution objects.
		 * \param newObjects The new vector of evolution objects.
		 */
		virtual void setEvolutionObjects(const std::vector<AbstractEvolutionObject*>& newObjects) = 0;
		/**
		 * \brief This method creates a new evolution object and per default adds it to the world.
		 * \param addToWorld True, if the new object should be added to this world.
		 * \return The new evolution object.
		 */
		virtual AbstractEvolutionObject* addNewObject(bool addToWorld = true) = 0;
		/**
		 * \brief Executes one simulation step.
		 * \details Does a whole new simulation after that new fitness values can be determined.
		 * \return True, if the learning rule should stop.
		 */
		virtual bool doSimulationStep() = 0;
		/**
		 * \brief Returns a list of all current evolution objects ordered by their score.
		 * \return The highscroe.
		 */
		virtual Highscore& getHighscoreList();
		/**
		 * \brief Returns the score of the given object.
		 * \param object The object to evaluate.
		 * \return The score of the object.
		 */
		virtual double getScore(const AbstractEvolutionObject& object) const = 0;
		/**
		 * \brief Initializes the world before the learning starts.
		 */
		virtual void initializeForLearning() {}
		/**
		 * \brief Resets the whole world so a new simulation can start.
		 */
		virtual void reset() = 0;
		/**
		* \brief Returns a vector of all data set labels which are available in this world.
		* \return The labels of all available data sets.
		*/
		virtual std::vector<std::string> getDataSetLabels() const;
		/**
		 * \brief Sets the learning state where all datasets should be stored in.
		 * \param learningState_ The learning state.
		 */
		void setLearningState(LearningState& learningState_);
		/**
		 * \brief Returns the current population size.
		 * \return The amount of objects.
		 */
		virtual int getPopulationSize() const = 0;
		/**
		* \brief Removes all evolution objects.
		*/
		virtual void clearPopulation() = 0;
		/**
		 * \brief Adds an existing object to the population.
		 * \param newObject The object to add.
		 */
		virtual void addExistingObject(AbstractEvolutionObject* newObject) = 0;
		/**
		 * \brief Recalculates the highscore.
		 */
		void refreshHighscore();
	};
}

EMPTY_SERIALIZATION(LightBulb::AbstractEvolutionWorld, LightBulb);

#endif
