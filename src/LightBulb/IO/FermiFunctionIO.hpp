#pragma once

#ifndef _FERMIFUNCTIONIO_H_
#define _FERMIFUNCTIONIO_H_

// Libary includes
#include <Function/ActivationFunction/FermiFunction.hpp>

#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a FermiFunction.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param fermiFunction The FermiFunction to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, FermiFunction& fermiFunction)
	{
		archive(cereal::make_nvp("temperatureParameter", fermiFunction.temperatureParameter));
	}
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::FermiFunction>
	{
		/**
		* \brief Constructs a FermiFunction.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The FermiFunction construct object.
		*/
		template <class Archive>
		static void load_and_construct(Archive & ar, construct<LightBulb::FermiFunction>& construct)
		{
			double temperatureParameter;
			ar(make_nvp("temperatureParameter", temperatureParameter));
			construct(temperatureParameter);
		}
	};
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::FermiFunction);

#endif
