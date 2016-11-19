#pragma once

#ifndef _ABSTRACTEVOLUTIONENVIRONMENT_H_
#define _ABSTRACTEVOLUTIONENVIRONMENT_H_

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
	class AbstractIndividual;
	/**
	 * \brief Describes a ranked list of all individuals depending on their fitness values.
	 */
	typedef std::vector<std::pair<double, AbstractIndividual*>> Highscore;
	/**
	 * \brief This class describes a environment which contains multiple individuals.
	 * \details The evolution environment has to simulate the environment which surrounds its individuals.
	 */
	class AbstractEvolutionEnvironment : public AbstractLoggable, public virtual AbstractRandomGeneratorUser
	{
	private:
		/**
		 * \brief The current highscore which ranks all individuals by their current fitness value.
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
		virtual ~AbstractEvolutionEnvironment() {}
		/**
		 * \brief Creates a evolution environment.
		 */
		AbstractEvolutionEnvironment();
		/**
		 * \brief Returns all current individuals.
		 * \return A vector of individuals.
		 */
		virtual std::vector<AbstractIndividual*>& getIndividuals() = 0;
		/**
		 * \brief Sets all individual.
		 * \param newIndividuals The new vector of individual.
		 */
		virtual void setIndividuals(const std::vector<AbstractIndividual*>& newIndividuals) = 0;
		/**
		 * \brief This method creates a new individual and per default adds it to the environment.
		 * \param addToEnvironment True, if the new individual should be added to this environment.
		 * \return The new individual.
		 */
		virtual AbstractIndividual* addNewIndividual(bool addToEnvironment = true) = 0;
		/**
		 * \brief Executes one simulation step.
		 * \details Does a whole new simulation after that new fitness values can be determined.
		 * \return True, if the learning rule should stop.
		 */
		virtual bool doSimulationStep() = 0;
		/**
		 * \brief Returns a list of all current individuals ordered by their score.
		 * \return The highscroe.
		 */
		virtual Highscore& getHighscoreList();
		/**
		 * \brief Returns the score of the given individual.
		 * \param individual The individual to evaluate.
		 * \return The score of the individual.
		 */
		virtual double getScore(const AbstractIndividual& individual) const = 0;
		/**
		 * \brief Initializes the environment before the learning starts.
		 */
		virtual void initializeForLearning() {}
		/**
		 * \brief Resets the whole environment so a new simulation can start.
		 */
		virtual void reset() = 0;
		/**
		* \brief Returns a vector of all data set labels which are available in this environment.
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
		 * \return The amount of individuals.
		 */
		virtual int getPopulationSize() const = 0;
		/**
		* \brief Removes all individuals.
		*/
		virtual void clearPopulation() = 0;
		/**
		 * \brief Adds an existing individual to the population.
		 * \param newIndividual The individual to add.
		 */
		virtual void addExistingIndividual(AbstractIndividual* newIndividual) = 0;
		/**
		 * \brief Recalculates the highscore.
		 */
		void refreshHighscore();
	};
}

EMPTY_SERIALIZATION(LightBulb::AbstractEvolutionEnvironment, LightBulb);

#endif
