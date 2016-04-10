#pragma once

#ifndef _STORAGELOGGERIO_H_
#define _STORAGELOGGERIO_H_

// Libary includes
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/cereal.hpp>
#include "Logging/StorageLogger.hpp"

template <class Archive>
void serialize(Archive& archive, StorageLogger& storageLogger)
{
	archive(cereal::make_nvp("messages", storageLogger.messages));
}

#endif
