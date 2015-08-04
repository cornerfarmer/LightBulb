#pragma once

#ifndef _LVQNETWORKSTRUCTURECHART_H_
#define _LVQNETWORKSTRUCTURECHART_H_

// Includes
#include "Graphics\AbstractNetworkStructureChart.hpp"

// Forward declarations
class LVQNetwork;

// This structure describes all options of an LVQNetworkStructureChart
struct LVQNetworkStructureChartOptions : public AbstractNetworkStructureChartOptions
{
	// The selected lvqNetwork
	LVQNetwork* lvqNetwork;	
	LVQNetworkStructureChartOptions()
	{
		lvqNetwork = NULL;
	}
};

// A chart which shows the location of the lvq neurons inside a lvqNetwork
class LVQNetworkStructureChart : public AbstractNetworkStructureChart
{
private:
	LVQNetworkStructureChartOptions* getOptions();
protected:
	std::vector<StandardNeuron*>* getNeurons();
	double getRadiusOfNeuron(StandardNeuron& neuron);
	std::vector<double> getPositionOfNeuron(StandardNeuron& neuron);
public:
	LVQNetworkStructureChart(LVQNetworkStructureChartOptions &options_);
};

#endif
