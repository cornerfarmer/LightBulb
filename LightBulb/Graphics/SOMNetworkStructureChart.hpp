#pragma once

#ifndef _SOMNETWORKSTRUCTURECHART_H_
#define _SOMNETWORKSTRUCTURECHART_H_

// Includes
#include "Graphics/AbstractNetworkStructureChart.hpp"

// Forward declarations
class SOMNetwork;

// This structure describes all options of an LVQNetworkStructureChart
struct SOMNetworkStructureChartOptions : public AbstractNetworkStructureChartOptions
{
	// The selected somNetwork
	SOMNetwork* somNetwork;	
	SOMNetworkStructureChartOptions()
	{
		somNetwork = NULL;
	}
};

// A chart which shows the structure of a som in the input space
class SOMNetworkStructureChart : public AbstractNetworkStructureChart
{
private:
	SOMNetworkStructureChartOptions* getOptions();
	sf::VertexArray lines;
protected:
	// Inherited
	std::vector<StandardNeuron*>* getNeurons();
	double getRadiusOfNeuron(StandardNeuron& neuron);
	std::vector<double> getPositionOfNeuron(StandardNeuron& neuron);
public:
	SOMNetworkStructureChart(SOMNetworkStructureChartOptions &options_);
	void draw(sf::RenderWindow &window);
	void recalculateAllValues();
};

#endif
