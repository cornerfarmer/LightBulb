#pragma once

#ifndef _LEARNINGSTATEIO_H_
#define _LEARNINGSTATEIO_H_

// Libary includes
#include <cereal/types/map.hpp>
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>
#include <Learning/LearningState.hpp>
#include <IO/IOStorage.hpp>

namespace LightBulb
{
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
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<LightBulb::LearningState>& construct)
		{
			using namespace LightBulb;
			int dataSaveInterval;
			ar(cereal::make_nvp("dataSaveInterval", dataSaveInterval));
			construct(*IOStorage<std::map<std::string, bool>>::pop(), dataSaveInterval);

			ar(cereal::make_nvp("dataSets", construct->dataSets));
			ar(cereal::make_nvp("iterationsNeeded", construct->iterations));
			ar(cereal::make_nvp("tries", construct->tries));
		}
	};
}

#endif
