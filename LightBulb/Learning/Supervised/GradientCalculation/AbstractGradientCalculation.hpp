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
		std::vector<Eigen::MatrixXd> gradient;
	protected:
		std::vector<Eigen::MatrixXd>* gradientToUse;
	public:
		void initGradient(AbstractNetworkTopology* networkTopology);
		std::vector<Eigen::MatrixXd>* getGradient();
		virtual void calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap);
		virtual void calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap, std::vector<Eigen::MatrixXd>& gradient);
		virtual void calcGradient(AbstractNetworkTopology* networkTopology, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, ErrorMap_t* errormap) = 0;
	};
}

EMPTY_SINGLE_SERIALIZATION(LightBulb::AbstractGradientCalculation, LightBulb)

#endif

