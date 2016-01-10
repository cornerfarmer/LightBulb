#pragma once

#ifndef _ABSTRACTHALLOFFAMEALGORITHM_H_
#define _ABSTRACTHALLOFFAMEALGORITHM_H_

// Library Includes
#include <vector>
#include <map>

// Include

// Forward declarations
class AbstractEvolutionObject;
class AbstractCoevolutionWorld;

class AbstractHallOfFameAlgorithm
{
private:
	AbstractCoevolutionWorld* currentWorld;
	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>* currentResults;
protected:
	std::vector<AbstractEvolutionObject*> members;
	void simulateAgainstMember(AbstractEvolutionObject* object, int memberID);
	virtual void evaluateObjects(std::vector<AbstractEvolutionObject*>& objects) = 0;
public:
	virtual void execute(AbstractCoevolutionWorld* world, std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>& prevResults);
	void addMember(AbstractEvolutionObject* newMember);
};

#endif
