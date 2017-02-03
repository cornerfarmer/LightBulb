#pragma once

#ifndef _POSITIONIO_H_
#define _POSITIONIO_H_

// Includes
#include "Examples/FunctionEvolution/Position.hpp"

template <class Archive>
extern void save(Archive& archive, Position const& individual);

template <class Archive>
extern void load(Archive& archive, Position& individual);

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(Position)

#endif