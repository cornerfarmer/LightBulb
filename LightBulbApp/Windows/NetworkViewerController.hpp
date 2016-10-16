#pragma once

#ifndef _NETWORKVIEWERCONTROLLER_H_
#define _NETWORKVIEWERCONTROLLER_H_

// Library includes
#include <vector>

// Includes
#include "NetworkViewerWindow.hpp"
#include "AbstractSubApp.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetworkRepository;
	class AbstractNeuralNetwork;

	class NetworkViewerController : public AbstractSubApp
	{
	private:
		std::unique_ptr<NetworkViewerWindow> window;
		NeuralNetworkRepository* neuralNetworkRepository;
	protected:
	public:
		NetworkViewerController(AbstractMainApp* mainApp, NeuralNetworkRepository* neuralNetworkRepository_, AbstractWindow* parent = nullptr);
		NetworkViewerWindow* getWindow();
		const std::vector<std::unique_ptr<AbstractNeuralNetwork>>* getNeuralNetworks() const;
		void neuralNetworksChanged(NeuralNetworkRepository* neuralNetworkRepository);
		static const std::string& getLabel();

	};
}

#endif
