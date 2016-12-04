#pragma once

#ifndef _ABSTRACTHALLOFFAMEALGORITHMIO_H_
#define _ABSTRACTHALLOFFAMEALGORITHMIO_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractHallOfFameAlgorithm
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param hallOfFameAlgorithm The AbstractHallOfFameAlgorithm to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractHallOfFameAlgorithm& hallOfFameAlgorithm)
	{
		archive(cereal::make_nvp("members", hallOfFameAlgorithm.members));
	}
}

#endif