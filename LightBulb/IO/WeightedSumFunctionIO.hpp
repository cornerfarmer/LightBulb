#pragma once

#ifndef _WEIGHTEDSUMFUNCTIONIO_H_
#define _WEIGHTEDSUMFUNCTIONIO_H_

// Libary includes
#include <Function/WeightedSumFunction.hpp>
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

template <class Archive>
void serialize(Archive& archive, WeightedSumFunction& weightedSumFunction)
{
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(WeightedSumFunction);

#endif
