#pragma once

#ifndef _LEARNINGSTATEIO_H_
#define _LEARNINGSTATEIO_H_

// Libary includes
#include <cereal/types/map.hpp>
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

// Includes
#include "LightBulb/Learning/LearningState.hpp"
#include "LightBulb/IO/IOStorage.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a LearningState.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningState The LearningState to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, LearningState& learningState)
	{
		archive(cereal::make_nvp("dataSaveInterval", learningState.dataSaveInterval));
		archive(cereal::make_nvp("dataSets", learningState.dataSets));
		archive(cereal::make_nvp("iterationsNeeded", learningState.iterations));
		archive(cereal::make_nvp("tries", learningState.tries));
	}
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::LearningState>
	{
		/**
		* \brief Constructs a LearningState.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The LearningState construct object.
		*/
		template <class Archive>
		static void load_and_construct(Archive & ar, construct<LightBulb::LearningState>& construct)
		{
			using namespace LightBulb;
			int dataSaveInterval;
			ar(make_nvp("dataSaveInterval", dataSaveInterval));
			construct(*IOStorage<std::map<std::string, bool>>::pop(), dataSaveInterval);

			ar(make_nvp("dataSets", construct->dataSets));
			ar(make_nvp("iterationsNeeded", construct->iterations));
			ar(make_nvp("tries", construct->tries));
		}
	};
}

#endif
