#pragma once

#ifndef _ABSTRACTGRADIENTCALCULATION_H_
#define _ABSTRACTGRADIENTCALCULATION_H_

// Includes
#include "IO/UseParentSerialization.hpp"

// Library Includes
#include <vector>
#include <EigenSrc/Dense>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;

	typedef std::vector<Eigen::VectorXd> ErrorMap_t;

	class AbstractGradientCalculation
	{
	private:
	public:
		std::vector<Eigen::MatrixXd> calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap);
		virtual void calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap, std::vector<Eigen::MatrixXd>& gradient) = 0;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractGradientCalculation, LightBulb)

#endif

