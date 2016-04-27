#pragma once

#ifndef _RANDOMHALLOFFAMEALGORITHM_H_
#define _RANDOMHALLOFFAMEALGORITHM_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"

// Forward declarations

class RandomHallOfFameAlgorithm : public AbstractHallOfFameAlgorithm
{
	template <class Archive>
	friend void serialize(Archive& archive, RandomHallOfFameAlgorithm& hallOfFameAlgorithm);
private:
	int amountOfCompetitionsPerObject;
protected:	
	void evaluateObjects(std::vector<AbstractEvolutionObject*>& objects);
public:
	RandomHallOfFameAlgorithm(int amountOfCompetitionsPerObject_ = 0);
};

#include "IO/RandomHallOfFameAlgorithmIO.hpp"

#endif
