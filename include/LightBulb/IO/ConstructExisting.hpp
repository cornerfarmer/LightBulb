#pragma once

#ifndef _CONSTRUCTEXISTING_H_
#define _CONSTRUCTEXISTING_H_

// Includes
#include "LightBulb/IO/IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

template <class SelfType, class T, class StorageType>
struct ConstructExisting
{
	/**
	 * \brief Constructs an existing objects, which will be retrieved from the IOStorage<T>.
	 * \tparam Archive The archive type.
	 * \param ar The archive which should be used.
	 * \param construct The construct object. (Will not really be used)
	 */
	template <class Archive>
	static void load_and_construct(Archive& ar, cereal::construct<T>& construct)
	{
		construct();
		T* storage = static_cast<T*>(LightBulb::IOStorage<StorageType>::pop());
		SelfType::construct(ar, *storage);
		LightBulb::IOStorage<StorageType>::push(storage);
	}
};

/**
 * \brief Constructs T from an existing object.
 * \param T The type which should be constructed.
 * \param StorageType The storage type which contains the existing object of T.
 * \note Before it can be used, make sure the existing object lies in IOStorage<StorageType>
 */
#define CONSTRUCT_EXISTING(T, StorageType) \
template <> \
struct LoadAndConstruct<T> : public ConstructExisting<LoadAndConstruct<T>, T, StorageType>


#endif