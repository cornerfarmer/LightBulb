#pragma once

#ifndef _FERMIFUNCTIONIO_H_
#define _FERMIFUNCTIONIO_H_

// Libary includes
#include <Function/GaussianRBFFunction.hpp>

#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include "IOStorage.hpp"

template <class Archive>
void serialize(Archive& archive, GaussianRBFFunction& gaussianRbfFunction)
{
}

namespace cereal
{
	template <> struct LoadAndConstruct<GaussianRBFFunction>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<GaussianRBFFunction>& construct)
		{
			construct(IOStorage<Eigen::VectorXd>::pop());
		}
	};
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(GaussianRBFFunction);

#endif
