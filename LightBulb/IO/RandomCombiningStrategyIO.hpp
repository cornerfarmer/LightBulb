#pragma once

#ifndef _RANDOMCOMBININGSTRATEGYIO_H_
#define _RANDOMCOMBININGSTRATEGYIO_H_

// Includes
#include "Learning/Evolution/RandomCombiningStrategy.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, RandomCombiningStrategy& randomCombiningStrategy)
{
	archive(cereal::make_nvp("amountOfCompetitionsPerObject", randomCombiningStrategy.amountOfCompetitionsPerObject));
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(RandomCombiningStrategy);

#endif