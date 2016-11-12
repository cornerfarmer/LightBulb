// Includes
#include "Windows/NetworkViewerController.hpp"
#include <Repositories/NeuralNetworkRepository.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>

namespace LightBulb
{
	NetworkViewerController::NetworkViewerController(AbstractMainApp& mainApp, NeuralNetworkRepository& neuralNetworkRepository_, AbstractWindow& parent)
		:AbstractSubApp(mainApp)
	{
		neuralNetworkRepository = &neuralNetworkRepository_;
		neuralNetworkRepository->registerObserver(EVT_NN_CHANGED, &NetworkViewerController::neuralNetworksChanged, *this);
		window = new NetworkViewerWindow(*this, parent);
		neuralNetworksChanged(*neuralNetworkRepository);
	}


	NetworkViewerWindow& NetworkViewerController::getWindow()
	{
		return *window;
	}

	const std::vector<std::unique_ptr<AbstractNeuralNetwork>>& NetworkViewerController::getNeuralNetworks() const
	{
		return neuralNetworkRepository->getNeuralNetworks();
	}


	void NetworkViewerController::neuralNetworksChanged(NeuralNetworkRepository& neuralNetworkRepository)
	{
		window->refreshNeuralNetworks();
	}


	std::string NetworkViewerController::getLabel()
	{
		return "Network viewer";
	}
}