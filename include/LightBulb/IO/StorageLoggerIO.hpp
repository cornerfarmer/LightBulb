#pragma once

#ifndef _STORAGELOGGERIO_H_
#define _STORAGELOGGERIO_H_

// Libary includes
#include "LightBulb/Logging/StorageLogger.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a StorageLogger.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param storageLogger The StorageLogger to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, StorageLogger& storageLogger);
}

#endif
