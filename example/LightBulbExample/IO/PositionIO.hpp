#pragma once

#ifndef _POSITIONIO_H_
#define _POSITIONIO_H_

// Includes
#include "Examples/FunctionEvolution/Position.hpp"

template <class Archive>
extern void save(Archive& archive, Position const& individual);

template <class Archive>
extern void load(Archive& archive, Position& individual);

#endif