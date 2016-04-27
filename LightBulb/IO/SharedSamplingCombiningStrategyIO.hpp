#pragma once

#ifndef _SHAREDSAMPLINGCOMBININGSTRATEGYIO_H_
#define _SHAREDSAMPLINGCOMBININGSTRATEGYIO_H_

// Includes
#include "Learning/Evolution/SharedSamplingCombiningStrategy.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, SharedSamplingCombiningStrategy& sharedSamplingCombiningStrategy)
{
	archive(cereal::make_nvp("amountOfCompetitionsPerObject", sharedSamplingCombiningStrategy.amountOfCompetitionsPerObject));
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(SharedSamplingCombiningStrategy)

#endif