#pragma once

#ifndef _SIMULATORCONTROLLER_H_
#define _SIMULATORCONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "SimulatorWindow.hpp"
#include "AbstractSubApp.hpp"

// Forward declarations
class TrainingWindow;
class TrainingController;
class NeuralNetworkRepository;
class AbstractNeuralNetwork;

class SimulatorController : public AbstractSubApp
{
private:
	std::unique_ptr<SimulatorWindow> window;
	NeuralNetworkRepository* neuralNetworkRepository;
protected:
	void prepareClose() override;
public:
	SimulatorController(AbstractMainApp* mainApp, NeuralNetworkRepository* neuralNetworkRepository_, AbstractWindow* parent = NULL);
	SimulatorWindow* getWindow();
	std::vector<std::unique_ptr<AbstractNeuralNetwork>>* getNeuralNetworks();
	void neuralNetworksChanged(NeuralNetworkRepository* neuralNetworkRepository);
	std::vector<double> calculate(int neuralNetworkIndex, std::vector<double> input);
	static std::string getLabel();
};

#endif
