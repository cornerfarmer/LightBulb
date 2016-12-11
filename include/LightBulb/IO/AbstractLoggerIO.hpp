#pragma once

#ifndef _ABSTRACTLOGGERIO_H_
#define _ABSTRACTLOGGERIO_H_

// Libary includes
#include "LightBulb/Logging/AbstractLogger.hpp"

#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a logger.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param logger The AbstractLogger to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractLogger& logger)
	{
		archive(cereal::make_nvp("currentLogLevel", logger.currentLogLevel));
	}
}

#endif
