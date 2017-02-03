#pragma once

#ifndef _TRAININGCONTROLLERIO_H_
#define _TRAININGCONTROLLERIO_H_

// Includes
#include "LightBulbApp/Windows/TrainingController.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a TrainingController.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingController The TrainingController to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, TrainingController& trainingController);
}

#endif
