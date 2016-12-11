#pragma once

#ifndef _USEPARENTSERIALIZATION_H_
#define _USEPARENTSERIALIZATION_H_

// Includes
#include "LightBulb/IO/ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>

#include "LightBulb/IO/UsedArchives.hpp"


/**
* \brief Creates save/load functions for T which just use its Parent serialization functions.
* \param T The type which is the target of the defined serialization functions.
* \param Parent The Parent type which serialization functions should be referenced.
* \param Namespace The namespace which should contain the new serialization functions.
*/
#define USE_PARENT_SERIALIZATION(T, Parent, Namespace) \
namespace Namespace { \
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
}\
CEREAL_REGISTER_TYPE(T);


/**
* \brief Creates save/load functions for T which just use its Parent serialization functions.
* \param T The type which is the target of the defined serialization functions.
* \param Parent The Parent type which serialization functions should be referenced.
*/
#define USE_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(T, Parent) \
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

/**
* \brief Creates a serialization function for T which just use its Parent serialization functions.
* \param T The type which is the target of the defined serialization function.
* \param Parent The Parent type which serialization functions should be referenced.
* \param Namespace The namespace which should contain the new serialization function.
*/
#define USE_PARENT_SINGLE_SERIALIZATION(T, Parent, Namespace) \
namespace Namespace { \
	template <class Archive> \
	void serialize(Archive& archive, T& trainingPlan) \
	{ \
		archive(cereal::base_class<Parent>(&trainingPlan)); \
	} \
} \
CEREAL_REGISTER_TYPE(T);

/**
* \brief Creates a serialization function for T which just use its Parent serialization functions.
* \param T The type which is the target of the defined serialization function.
* \param Parent The Parent type which serialization functions should be referenced.
*/
#define USE_PARENT_SINGLE_SERIALIZATION_WITHOUT_NAMESPACE(T, Parent) \
template <class Archive> \
void serialize(Archive& archive, T& trainingPlan) \
{ \
	archive(cereal::base_class<Parent>(&trainingPlan)); \
} \
CEREAL_REGISTER_TYPE(T);

/**
* \brief Creates a empty serialization function for a child class T.
* \param T The type which is the target of the defined serialization function.
* \param Namespace The namespace which should contain the new serialization function.
*/
#define EMPTY_CHILD_SERIALIZATION(T, Namespace) \
namespace Namespace { \
	template <class Archive> \
	void serialize(Archive& archive, T& trainingPlan) \
	{ \
	} \
} \
CEREAL_REGISTER_TYPE(T);

/**
* \brief Creates a empty serialization function for a child class T.
* \param T The type which is the target of the defined serialization function.
*/
#define EMPTY_CHILD_SERIALIZATION_WITHOUT_NAMESPACE(T) \
template <class Archive> \
void serialize(Archive& archive, T& trainingPlan) \
{ \
} \
CEREAL_REGISTER_TYPE(T);


/**
* \brief Creates empty save/load functions for T.
* \param T The type which is the target of the defined serialization functions.
* \param Namespace The namespace which should contain the new serialization functions.
*/
#define EMPTY_SERIALIZATION(T, Namespace) \
namespace Namespace { \
	template <class Archive> \
	void save(Archive& archive, T const& trainingPlan) \
	{ \
	} \
	template <class Archive> \
	void load(Archive& archive, T& trainingPlan) \
	{ \
	} \
}

/**
* \brief Creates empty save/load functions for T.
* \param T The type which is the target of the defined serialization functions.
*/
#define EMPTY_SERIALIZATION_WITHOUT_NAMESPACE(T) \
template <class Archive> \
void save(Archive& archive, T const& trainingPlan) \
{ \
} \
template <class Archive> \
void load(Archive& archive, T& trainingPlan) \
{ \
} \

/**
* \brief Creates a empty serialization function for T.
* \param T The type which is the target of the defined serialization function.
* \param Namespace The namespace which should contain the new serialization function.
*/
#define EMPTY_SINGLE_SERIALIZATION(T, Namespace) \
namespace Namespace { \
	template <class Archive> \
	void serialize(Archive& archive, T& trainingPlan) \
	{ \
	} \
} 

/**
* \brief Creates a empty serialization function for T.
* \param T The type which is the target of the defined serialization function.
*/
#define EMPTY_SINGLE_SERIALIZATION_WITHOUT_NAMESPACE(T) \
template <class Archive> \
void serialize(Archive& archive, T& trainingPlan) \
{ \
} \

 /**
 * \brief Creates save/load functions for an existing T which just use its Parent serialization functions.
 * \param T The type which is the target of the defined serialization functions.
 * \param Parent The Parent type which serialization functions should be referenced.
 * \param StorageType The storage type which contains the existing object of T.
 * \param Namespace The namespace which should contain the new serialization functions.
 */
#define USE_EXISTING_PARENT_SERIALIZATION(T, Parent, StorageType, Namespace) \
namespace Namespace { \
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

 /**
 * \brief Creates save/load functions for an existing T which just use its Parent serialization functions.
 * \param T The type which is the target of the defined serialization functions.
 * \param Parent The Parent type which serialization functions should be referenced.
 * \param StorageType The storage type which contains the existing object of T.
 */
#define USE_EXISTING_PARENT_SERIALIZATION_WITHOUT_NAMESPACE(T, Parent, StorageType) \
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

 /**
 * \brief Creates a serialization function for an existing T which just use its Parent serialization functions.
 * \param T The type which is the target of the defined serialization function.
 * \param Parent The Parent type which serialization functions should be referenced.
 * \param StorageType The storage type which contains the existing object of T.
 * \param Namespace The namespace which should contain the new serialization function.
 */
#define USE_EXISTING_PARENT_SINGLE_SERIALIZATION(T, Parent, StorageType, Namespace) \
namespace Namespace { \
	template <class Archive> \
	void serialize(Archive& archive, T& trainingPlan) \
	{ \
		archive(cereal::base_class<Parent>(&trainingPlan)); \
	} \
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


 /**
 * \brief Creates a serialization function for an existing T which just use its Parent serialization functions.
 * \param T The type which is the target of the defined serialization function.
 * \param Parent The Parent type which serialization functions should be referenced.
 * \param StorageType The storage type which contains the existing object of T.
 */
#define USE_EXISTING_PARENT_SINGLE_SERIALIZATION_WITHOUT_NAMESPACE(T, Parent, StorageType) \
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