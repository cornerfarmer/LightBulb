#pragma once

#ifndef _ABSTRACTHALLOFFAMEALGORITHMIO_H_
#define _ABSTRACTHALLOFFAMEALGORITHMIO_H_

// Includes
#include "Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, AbstractHallOfFameAlgorithm& hallOfFameAlgorithm)
{
	archive(cereal::make_nvp("members", hallOfFameAlgorithm.members));
}

#endif