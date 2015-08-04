#pragma once

#ifndef _RBFNETWORKSTRUCTURECHART_H_
#define _RBFNETWORKSTRUCTURECHART_H_

// Includes
#include "Graphics\AbstractNetworkStructureChart.hpp"

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
	std::vector<StandardNeuron*>* getNeurons();
	double getRadiusOfNeuron(StandardNeuron& neuron);
	std::vector<double> getPositionOfNeuron(StandardNeuron& neuron);
public:
	RBFNetworkStructureChart(RBFNetworkStructureChartOptions &options_);
};

#endif
