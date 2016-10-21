#pragma once

#ifndef _SIMULATORCONTROLLER_H_
#define _SIMULATORCONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "SimulatorWindow.hpp"
#include "AbstractSubApp.hpp"

namespace LightBulb
{
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
		SimulatorController(AbstractMainApp& mainApp, NeuralNetworkRepository& neuralNetworkRepository_, AbstractWindow* parent = nullptr);
		SimulatorWindow& getWindow();
		const std::vector<std::unique_ptr<AbstractNeuralNetwork>>& getNeuralNetworks();
		void neuralNetworksChanged(NeuralNetworkRepository& neuralNetworkRepository);
		std::vector<double> calculate(int neuralNetworkIndex, const std::vector<double>& input);
		static std::string getLabel();
	};
}

#endif
