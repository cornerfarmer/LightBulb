#pragma once

#ifndef _FERMIFUNCTIONIO_H_
#define _FERMIFUNCTIONIO_H_

// Libary includes
#include <Function/FermiFunction.hpp>
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

template <class Archive>
void serialize(Archive& archive, FermiFunction& fermiFunction)
{
	archive(cereal::make_nvp("temperatureParameter", fermiFunction.temperatureParameter));
}

namespace cereal
{
	template <> struct LoadAndConstruct<FermiFunction>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<FermiFunction>& construct)
		{
			double temperatureParameter;
			ar(cereal::make_nvp("temperatureParameter", temperatureParameter));
			construct(temperatureParameter);
		}
	};
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(FermiFunction);

#endif
