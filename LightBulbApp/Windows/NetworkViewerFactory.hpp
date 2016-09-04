#pragma once

#ifndef _NETWORKVIEWERFACTORY_H_
#define _NETWORKVIEWERFACTORY_H_

// Includes
#include "AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

// Forward declarations
class NeuralNetworkRepository;

class NetworkViewerFactory : public AbstractSubAppFactory
{
protected:
	NeuralNetworkRepository* neuralNetworkRepository;
public:
	NetworkViewerFactory(NeuralNetworkRepository* neuralNetworkRepository_);
	AbstractSubApp* createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent) override;
	std::string getLabel() override;
};

#endif
