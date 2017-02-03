#pragma once

#ifndef _ABSTRACTLOGGERIO_H_
#define _ABSTRACTLOGGERIO_H_

// Libary includes
#include "LightBulb/Logging/AbstractLogger.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a logger.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param logger The AbstractLogger to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, AbstractLogger& logger);
}

#endif
