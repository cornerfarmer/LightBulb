#pragma once

#ifndef _TEACHEDEVOLUTIONOBJECTIO_H_
#define _TEACHEDEVOLUTIONOBJECTIO_H_

// Includes
#include <Learning/Evolution/TeachedEvolutionObject.hpp>
#include "IO/IOStorage.hpp"
#include "Learning/Evolution/TeachingEvolutionWorld.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	template <class Archive>
	void save(Archive& archive, TeachedEvolutionObject const& object)
	{
		archive(cereal::base_class<AbstractEvolutionObject>(&object));
		archive(cereal::make_nvp("neuralNetwork", object.neuralNetwork));
	}

	template <class Archive>
	void load(Archive& archive, TeachedEvolutionObject& object)
	{
		archive(cereal::base_class<AbstractEvolutionObject>(&object));
		archive(cereal::make_nvp("neuralNetwork", object.neuralNetwork));
		object.teachingEvolutionWorld = static_cast<TeachingEvolutionWorld*>(IOStorage<AbstractEvolutionWorld>::get());
		object.doNNCalculation();
	}
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::TeachedEvolutionObject);

#endif