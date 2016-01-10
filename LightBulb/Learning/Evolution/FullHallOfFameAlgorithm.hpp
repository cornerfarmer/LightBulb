#pragma once

#ifndef _FULLHALLOFFAMEALGORITHM_H_
#define _FULLHALLOFFAMEALGORITHM_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"

// Forward declarations

class FullHallOfFameAlgorithm : public AbstractHallOfFameAlgorithm
{
private:
protected:	
	void evaluateObjects(std::vector<AbstractEvolutionObject*>& objects);
};

#endif
