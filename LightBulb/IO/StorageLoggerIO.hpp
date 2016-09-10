#pragma once

#ifndef _STORAGELOGGERIO_H_
#define _STORAGELOGGERIO_H_

// Libary includes
#include "Logging/StorageLogger.hpp"

#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/cereal.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, StorageLogger& storageLogger)
	{
		archive(cereal::make_nvp("messages", storageLogger.messages));
	}
}

#endif
