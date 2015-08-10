#pragma once

#ifndef _COUNTERPROPAGATIONNETWORKSTRUCTURECHART_H_
#define _COUNTERPROPAGATIONNETWORKSTRUCTURECHART_H_

// Includes
#include "Graphics\AbstractNetworkStructureChart.hpp"

// Forward declarations
class CounterpropagationNetwork;

// This structure describes all options of an LVQNetworkStructureChart
struct CounterpropagationNetworkStructureChartOptions : public AbstractNetworkStructureChartOptions
{
	// The selected lvqNetwork
	CounterpropagationNetwork* network;	
	CounterpropagationNetworkStructureChartOptions()
	{
		network = NULL;
	}
};

// A chart which shows the location of the lvq neurons inside a lvqNetwork
class CounterpropagationNetworkStructureChart : public AbstractNetworkStructureChart
{
private:
	CounterpropagationNetworkStructureChartOptions* getOptions();
protected:
	std::vector<StandardNeuron*>* getNeurons();
	double getRadiusOfNeuron(StandardNeuron& neuron);
	std::vector<double> getPositionOfNeuron(StandardNeuron& neuron);
public:
	CounterpropagationNetworkStructureChart(CounterpropagationNetworkStructureChartOptions &options_);
};

#endif
