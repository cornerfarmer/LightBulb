#pragma once

#ifndef _FERMIFUNCTIONIO_H_
#define _FERMIFUNCTIONIO_H_

// Libary includes

// Includes
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a FermiFunction.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param fermiFunction The FermiFunction to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, FermiFunction& fermiFunction);
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
		static void load_and_construct(Archive & ar, construct<LightBulb::FermiFunction>& construct);
	};
}

#endif
