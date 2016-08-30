#pragma once

#ifndef _ABSTRACTGRADIENTCALCULATION_H_
#define _ABSTRACTGRADIENTCALCULATION_H_

// Library Includes
#include <vector>
#include <EigenSrc/Dense>

// Includes

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

#endif

