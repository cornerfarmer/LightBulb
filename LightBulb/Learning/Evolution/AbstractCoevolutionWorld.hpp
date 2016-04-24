#pragma once

#ifndef _ABSTRACTCOEVOLUTIONWORLD_H_
#define _ABSTRACTCOEVOLUTIONWORLD_H_

// Library Includes
#include <map>

// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"

// Forward declarations

#define DATASET_AVG_WINS "Average wins"
#define DATASET_PARASITE_PREFIX "Parasite - "

class AbstractCoevolutionWorld : public AbstractSimpleEvolutionWorld
{
	template <class Archive>
	friend void serialize(Archive& archive, AbstractCoevolutionWorld& world);
private:
	std::unique_ptr<AbstractCoevolutionFitnessFunction> fitnessFunction;
	std::shared_ptr<AbstractHallOfFameAlgorithm> hallOfFameToAddAlgorithm;
	std::shared_ptr<AbstractHallOfFameAlgorithm> hallOfFameToChallengeAlgorithm;
	std::unique_ptr<AbstractCombiningStrategy> combiningStrategy;
	std::map<AbstractEvolutionObject*, double> fitnessValues;
protected:
	bool isParasiteWorld;
public:
	AbstractCoevolutionWorld(bool isParasiteWorld_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = NULL, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = NULL);
	bool doSimulationStep(); 
	double getScore(AbstractEvolutionObject* object);
	virtual int compareObjects(AbstractEvolutionObject* obj1, AbstractEvolutionObject* obj2) = 0;
	virtual int rateKI(AbstractEvolutionObject* rateKI) { return 0; };
	void setLogger(AbstractLogger* logger_);
	std::vector<std::string> getDataSetLabels();
};

#include "IO/AbstractCoevolutionWorldIO.hpp"

#endif
