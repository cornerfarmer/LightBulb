// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/Windows/NetworkViewerController.hpp"
#include "LightBulbApp/Repositories/NeuralNetworkRepository.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"

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

	void NetworkViewerController::prepareClose()
	{
		neuralNetworkRepository->removeObserver(EVT_NN_CHANGED, &NetworkViewerController::neuralNetworksChanged, *this);
	}


	std::string NetworkViewerController::getLabel()
	{
		return "Network viewer";
	}
}