#pragma once

#ifndef _USEPARENTSERIALIZATION_H_
#define _USEPARENTSERIALIZATION_H_

// Includes
#include "IO/ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>

#include "IO/UsedArchives.hpp"

#define USE_PARENT_SERIALIZATION(T, Parent) \
template <class Archive> \
void save(Archive& archive, T const& trainingPlan) \
{ \
	archive(cereal::base_class<Parent>(&trainingPlan)); \
} \
template <class Archive> \
void load(Archive& archive, T& trainingPlan) \
{ \
	archive(cereal::base_class<Parent>(&trainingPlan)); \
} \
CEREAL_REGISTER_TYPE(T);


#define USE_PARENT_SINGLE_SERIALIZATION(T, Parent) \
template <class Archive> \
void serialize(Archive& archive, T& trainingPlan) \
{ \
	archive(cereal::base_class<Parent>(&trainingPlan)); \
} \
CEREAL_REGISTER_TYPE(T);

#define EMPTY_CHILD_SERIALIZATION(T) \
template <class Archive> \
void serialize(Archive& archive, T& trainingPlan) \
{ \
} \
CEREAL_REGISTER_TYPE(T);

#define EMPTY_SERIALIZATION(T) \
template <class Archive> \
void save(Archive& archive, T const& trainingPlan) \
{ \
} \
template <class Archive> \
void load(Archive& archive, T& trainingPlan) \
{ \
} \

#define USE_EXISTING_PARENT_SERIALIZATION(T, Parent, StorageType) \
template <class Archive> \
void save(Archive& archive, T const& trainingPlan) \
{ \
	archive(cereal::base_class<Parent>(&trainingPlan)); \
} \
template <class Archive> \
void load(Archive& archive, T& trainingPlan) \
{ \
	archive(cereal::base_class<Parent>(&trainingPlan)); \
} \
namespace cereal \
{ \
	CONSTRUCT_EXISTING(T, StorageType) \
	{ \
		template <class Archive> \
		static void construct(Archive& ar, T& trainingPlan) \
		{ \
			ar(cereal::base_class<Parent>(&trainingPlan)); \
		} \
	}; \
} \
CEREAL_REGISTER_TYPE(T);

#define USE_EXISTING_PARENT_SINGLE_SERIALIZATION(T, Parent, StorageType) \
template <class Archive> \
void serialize(Archive& archive, T& trainingPlan) \
{ \
	archive(cereal::base_class<Parent>(&trainingPlan)); \
} \
namespace cereal \
{ \
	CONSTRUCT_EXISTING(T, StorageType) \
	{ \
		template <class Archive> \
		static void construct(Archive& ar, T& trainingPlan) \
		{ \
			ar(cereal::base_class<Parent>(&trainingPlan)); \
		} \
	}; \
} \
CEREAL_REGISTER_TYPE(T);




#endif