#pragma once

#ifndef _RBFNETWORKSTRUCTURECHART_H_
#define _RBFNETWORKSTRUCTURECHART_H_

// Includes
#include "Graphics/AbstractNetworkStructureChart.hpp"

// Forward declarations
class RBFNetwork;

// This structure describes all options of an RBFNetworkStructureChart
struct RBFNetworkStructureChartOptions : public AbstractNetworkStructureChartOptions
{
	// The selected rbfNetwork
	RBFNetwork* rbfNetwork;	
	RBFNetworkStructureChartOptions()
	{
		rbfNetwork = NULL;
	}
};

// A chart which shows the location of the rbf neurons inside a rbfNetwork
class RBFNetworkStructureChart : public AbstractNetworkStructureChart
{
private:
	RBFNetworkStructureChartOptions* getOptions();
protected:
	// Inherited:
	int getNeuronCount();
	double getRadiusOfNeuron(int neuronIndex);
	std::vector<double> getPositionOfNeuron(int neuronIndex);
public:
	RBFNetworkStructureChart(RBFNetworkStructureChartOptions &options_);
};

#endif
