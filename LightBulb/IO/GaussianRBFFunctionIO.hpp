#pragma once

#ifndef _FERMIFUNCTIONIO_H_
#define _FERMIFUNCTIONIO_H_

// Libary includes
#include <Function/ActivationFunction/GaussianRBFFunction.hpp>

#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include "IOStorage.hpp"

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, GaussianRBFFunction& gaussianRbfFunction)
	{
	}
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::GaussianRBFFunction>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<LightBulb::GaussianRBFFunction>& construct)
		{
			construct(LightBulb::IOStorage<Eigen::VectorXd>::pop());
		}
	};
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::GaussianRBFFunction);

#endif
