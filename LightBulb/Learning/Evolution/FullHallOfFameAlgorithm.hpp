#pragma once

#ifndef _FULLHALLOFFAMEALGORITHM_H_
#define _FULLHALLOFFAMEALGORITHM_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations

class FullHallOfFameAlgorithm : public AbstractHallOfFameAlgorithm
{
private:
protected:	
	void evaluateObjects(std::vector<AbstractEvolutionObject*>& objects);
};

USE_EXISTING_PARENT_SINGLE_SERIALIZATION(FullHallOfFameAlgorithm, AbstractHallOfFameAlgorithm, AbstractHallOfFameAlgorithm)

#endif
