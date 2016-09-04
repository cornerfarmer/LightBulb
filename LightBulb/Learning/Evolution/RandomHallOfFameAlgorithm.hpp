#pragma once

#ifndef _RANDOMHALLOFFAMEALGORITHM_H_
#define _RANDOMHALLOFFAMEALGORITHM_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations

class RandomHallOfFameAlgorithm : public AbstractHallOfFameAlgorithm
{
private:
	int amountOfCompetitionsPerObject;
protected:	
	void evaluateObjects(std::vector<AbstractEvolutionObject*>& objects) override;
public:
	RandomHallOfFameAlgorithm(int amountOfCompetitionsPerObject_ = 0);
};

USE_EXISTING_PARENT_SINGLE_SERIALIZATION(RandomHallOfFameAlgorithm, AbstractHallOfFameAlgorithm, AbstractHallOfFameAlgorithm)

#endif
