#pragma once

#ifndef _ABSTRACTCOEVOLUTIONENVIRONMENT_H_
#define _ABSTRACTCOEVOLUTIONENVIRONMENT_H_

// Library Includes
#include <map>

// Include
#include "Learning/Evolution/AbstractSimpleEvolutionEnvironment.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "AbstractCoevolutionFitnessFunction.hpp"

// Forward declarations

#define DATASET_AVG_WINS "Average wins"
#define DATASET_COMP "Comparisons in M"
#define DATASET_PARASITE_PREFIX "Parasite - "

namespace LightBulb
{
	/**
	 * \brief Describes a coevolution environment which evolves through competing with another coevolution environment.
	 */
	class AbstractCoevolutionEnvironment : public AbstractSimpleEvolutionEnvironment
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractCoevolutionEnvironment const& environment);
		template <class Archive>
		friend void load(Archive& archive, AbstractCoevolutionEnvironment& environment);
	private:
		/**
		 * \brief The fitness function which computes the fitness values from the combining results.
		 */
		std::unique_ptr<AbstractCoevolutionFitnessFunction> fitnessFunction;
		/**
		 * \brief The algorithm where to add new hall of fame members.
		 */
		std::shared_ptr<AbstractHallOfFameAlgorithm> hallOfFameToAddAlgorithm;
		/**
		 * \brief The algorithm which should be used for challenging.
		 */
		std::shared_ptr<AbstractHallOfFameAlgorithm> hallOfFameToChallengeAlgorithm;
		/**
		 * \brief The combining strategy which determines which individuals should compete.
		 */
		std::unique_ptr<AbstractCombiningStrategy> combiningStrategy;
		/**
		 * \brief The current fitness values.
		 */
		std::unique_ptr<std::map<const AbstractIndividual*, double>> fitnessValues;
	protected:
		/**
		 * \brief True, if this environment is the parasite environment.
		 */
		bool parasiteEnvironment;
		/**
		 * \brief Contains the total amount of comparisons.
		 */
		int comparisons;
		/**
		 * \brief Compares the two given individuals.
		 * \param individual1 The first individual.
		 * \param individual2 The second individual.
		 * \param round The round number.
		 * \return Return 1 if individual1 has won, -1 if individual2 has won.
		 */
		virtual int doCompare(AbstractIndividual& individual1, AbstractIndividual& individual2, int round) = 0;
	public:
		/**
		 * \brief Creates a coevolution environment.
		 * \param isParasiteEnvironment_ True, if this environment is the parasite environment.
		 * \param combiningStrategy_ The combining strategy which determines which individuals should compete.
		 * \param fitnessFunction_ The fitness function which computes the fitness values from the combining results.
		 * \param hallOfFameToAddAlgorithm_ The algorithm where to add new hall of fame members.
		 * \param hallOfFameToChallengeAlgorithm_ The algorithm which should be used for challenging.
		 */
		AbstractCoevolutionEnvironment(bool isParasiteEnvironment_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = nullptr, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = nullptr);
		AbstractCoevolutionEnvironment() = default;
		/**
		 * \brief Compares the two given individuals. 
		 * \param individual1 The first individual.
		 * \param individual2 The second individual.
		 * \param round The round number.
		 * \return Return 1 if individual1 has won, -1 if individual2 has won.
		 */
		virtual int compareIndividuals(AbstractIndividual& individual1, AbstractIndividual& individual2, int round);
		/**
		 * \brief Rates the given individual. (For debugging purposes)
		 * \param individual The individual to rate.
		 * \return The rating.
		 */
		virtual int rateIndividual(AbstractIndividual& individual) { return 0; }
		/**
		 * \brief Returns the combining strategy.
		 * \return The combining strategy.
		 */
		virtual AbstractCombiningStrategy& getCombiningStrategy() const;
		/**
		 * \brief Returns, if the environment is the parasite environment.
		 * \return True, if this environment is the parasite environment.
		 */
		virtual bool isParasiteEnvironment() const;
		/**
		 * \brief Returns how many rounds each individual pair should compete.
		 * \return The amount of rounds.
		 */
		virtual int getRoundCount() const;
		// Inherited:
		bool doSimulationStep() override;
		double getFitness(const AbstractIndividual& individual) const override;
		void setLogger(AbstractLogger& logger_) override;
		std::vector<std::string> getDataSetLabels() const override;
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
	};
}

#include "IO/AbstractCoevolutionEnvironmentIO.hpp"

#endif
