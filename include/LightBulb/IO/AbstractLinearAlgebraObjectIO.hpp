#pragma once

#ifndef _ABSTRACTLINEARALGEBRAOBJECTIO_H_
#define _ABSTRACTLINEARALGEBRAOBJECTIO_H_

// Includes
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraObject.hpp"
#include "LightBulb/IO/MatrixIO.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractLinearAlgebraObject.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param linearAlgebraObject The AbstractLinearAlgebraObject to save.
	*/
	template <class Archive, class EigenT, class ViennaCLT>
	void save(Archive& archive, AbstractLinearAlgebraObject<EigenT, ViennaCLT> const& linearAlgebraObject)
	{
		archive(cereal::make_nvp("eigenValue", linearAlgebraObject.eigenValue));
	}

	/**
	* \brief Loads an AbstractLinearAlgebraObject.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param linearAlgebraObject The AbstractLinearAlgebraObject to load.
	*/
	template <class Archive, class EigenT, class ViennaCLT>
	void load(Archive& archive, AbstractLinearAlgebraObject<EigenT, ViennaCLT>& linearAlgebraObject)
	{
		archive(cereal::make_nvp("eigenValue", linearAlgebraObject.eigenValue));
	}
}

#endif