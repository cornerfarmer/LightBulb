#pragma once

#ifndef _SIMULATORCONTROLLER_H_
#define _SIMULATORCONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "SimulatorWindow.hpp"

// Forward declarations
class TrainingWindow;
class TrainingController;
class NeuralNetworkRepository;
class AbstractNeuralNetwork;

class SimulatorController
{
private:
	std::unique_ptr<SimulatorWindow> window;
	TrainingController* trainingController;
	NeuralNetworkRepository* neuralNetworkRepository;
public:
	SimulatorController(NeuralNetworkRepository* neuralNetworkRepository_, AbstractWindow* parent = NULL);
	SimulatorWindow* getWindow();
	std::vector<std::unique_ptr<AbstractNeuralNetwork>>* getNeuralNetworks();
	void neuralNetworksChanged(NeuralNetworkRepository* neuralNetworkRepository);
	std::vector<double> calculate(int neuralNetworkIndex, std::vector<double> input);
};

#endif
