#pragma once

#ifndef _CONSTRUCTEXISTING_H_
#define _CONSTRUCTEXISTING_H_

// Includes
#include "IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

template <class SelfType, class T, class StorageType>
struct ConstructExisting
{
	template <class Archive>
	static void load_and_construct(Archive& ar, cereal::construct<T>& construct)
	{
		construct();
		T* storage = static_cast<T*>(LightBulb::IOStorage<StorageType>::pop());
		SelfType::construct(ar, *storage);
		LightBulb::IOStorage<StorageType>::push(storage);
	}
};

#define CONSTRUCT_EXISTING(T, StorageType) \
template <> \
struct LoadAndConstruct<T> : public ConstructExisting<LoadAndConstruct<T>, T, StorageType>


#endif