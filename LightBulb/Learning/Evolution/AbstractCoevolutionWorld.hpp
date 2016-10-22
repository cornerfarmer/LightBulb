#pragma once

#ifndef _ABSTRACTCOEVOLUTIONWORLD_H_
#define _ABSTRACTCOEVOLUTIONWORLD_H_

// Library Includes
#include <map>

// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "AbstractCoevolutionFitnessFunction.hpp"

// Forward declarations

#define DATASET_AVG_WINS "Average wins"
#define DATASET_COMP "Comparisons in M"
#define DATASET_PARASITE_PREFIX "Parasite - "

namespace LightBulb
{
	class AbstractCoevolutionWorld : public AbstractSimpleEvolutionWorld
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractCoevolutionWorld const& world);
		template <class Archive>
		friend void load(Archive& archive, AbstractCoevolutionWorld& world);
	private:
		std::unique_ptr<AbstractCoevolutionFitnessFunction> fitnessFunction;
		std::shared_ptr<AbstractHallOfFameAlgorithm> hallOfFameToAddAlgorithm;
		std::shared_ptr<AbstractHallOfFameAlgorithm> hallOfFameToChallengeAlgorithm;
		std::unique_ptr<AbstractCombiningStrategy> combiningStrategy;
		std::unique_ptr<std::map<AbstractEvolutionObject*, double>> fitnessValues;
	protected:
		bool parasiteWorld;
		int comparisons;
		virtual int doCompare(AbstractEvolutionObject& obj1, AbstractEvolutionObject& obj2, int round) = 0;
	public:
		AbstractCoevolutionWorld(bool isParasiteWorld_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = nullptr, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = nullptr);
		AbstractCoevolutionWorld() = default;
		bool doSimulationStep() override;
		double getScore(AbstractEvolutionObject& object) override;
		virtual int compareObjects(AbstractEvolutionObject& obj1, AbstractEvolutionObject& obj2, int round);
		virtual int rateKI(AbstractEvolutionObject& rateKI) { return 0; }
		virtual AbstractCombiningStrategy* getCombiningStrategy();
		void setLogger(AbstractLogger& logger_) override;
		std::vector<std::string> getDataSetLabels() override;
		virtual bool isParasiteWorld();
		virtual int getRoundCount();
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
	};
}

#include "IO/AbstractCoevolutionWorldIO.hpp"

#endif
