#pragma once

#ifndef _ABSTRACTEVOLUTIONOBJECTIO_H_
#define _ABSTRACTEVOLUTIONOBJECTIO_H_

// Includes
#include "Learning/Evolution/AbstractEvolutionObject.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, AbstractEvolutionObject& object)
{
	archive(cereal::make_nvp("mutationStrength", object.mutationStrength));
}


#endif