#pragma once

#ifndef _RANDOMHALLOFFAMEALGORITHMIO_H_
#define _RANDOMHALLOFFAMEALGORITHMIO_H_

// Includes
#include "Learning/Evolution/RandomHallOfFameAlgorithm.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, RandomHallOfFameAlgorithm& hallOfFameAlgorithm)
{
	archive(cereal::base_class<AbstractHallOfFameAlgorithm>(&hallOfFameAlgorithm));
	archive(cereal::make_nvp("amountOfCompetitionsPerObject", hallOfFameAlgorithm.amountOfCompetitionsPerObject));
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(RandomHallOfFameAlgorithm)

#endif