#pragma once

#ifndef _ABSTRACTHALLOFFAMEALGORITHM_H_
#define _ABSTRACTHALLOFFAMEALGORITHM_H_

// Library Includes
#include <vector>
#include <map>

// Include
#include "Logging/AbstractLoggable.hpp"
#include "AbstractEvolutionObject.hpp"

// Forward declarations
class AbstractCoevolutionWorld;

class AbstractHallOfFameAlgorithm : public AbstractLoggable
{
	template <class Archive>
	friend void serialize(Archive& archive, AbstractHallOfFameAlgorithm& hallOfFameAlgorithm);
private:
	AbstractCoevolutionWorld* currentWorld;
	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>* currentResults;
protected:
	std::vector<std::unique_ptr<AbstractEvolutionObject>> members;
	void simulateAgainstMember(AbstractEvolutionObject* object, int memberID);
	virtual void evaluateObjects(std::vector<AbstractEvolutionObject*>& objects) = 0;
public:
	virtual void execute(AbstractCoevolutionWorld* world, std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>& prevResults);
	void addMember(AbstractEvolutionObject* newMember);
};

#include "IO/AbstractHallOfFameAlgorithmIO.hpp"

#endif
