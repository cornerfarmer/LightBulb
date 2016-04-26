#pragma once

#ifndef _ABSTRACTEVOLUTIONOBJECTIO_H_
#define _ABSTRACTEVOLUTIONOBJECTIO_H_

// Includes
#include "Learning/Evolution/AbstractEvolutionObject.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, AbstractEvolutionObject const& object)
{
	archive(cereal::make_nvp("mutationStrength", object.mutationStrength));
}

template <class Archive>
void load(Archive& archive, AbstractEvolutionObject& object)
{
	archive(cereal::make_nvp("mutationStrength", object.mutationStrength));
}


#endif