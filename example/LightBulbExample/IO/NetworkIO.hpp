#pragma once

#ifndef _NETWORKIO_H_
#define _NETWORKIO_H_

// Includes
#include "Examples/NetworkEvolution/Network.hpp"

template <class Archive>
extern void save(Archive& archive, Network const& individual);

template <class Archive>
extern void load(Archive& archive, Network& individual);

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(Network)

#endif