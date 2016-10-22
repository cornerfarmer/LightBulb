#pragma once

#ifndef _NETWORKVIEWERFACTORY_H_
#define _NETWORKVIEWERFACTORY_H_

// Includes
#include "AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetworkRepository;

	class NetworkViewerFactory : public AbstractSubAppFactory
	{
	protected:
		NeuralNetworkRepository* neuralNetworkRepository;
	public:
		NetworkViewerFactory(NeuralNetworkRepository& neuralNetworkRepository_);
		AbstractSubApp* createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const override;
		std::string getLabel() const override;
	};
}

#endif
