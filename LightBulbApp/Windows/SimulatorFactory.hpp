#pragma once

#ifndef _SIMULATORFACTORY_H_
#define _SIMULATORFACTORY_H_

// Includes
#include "AbstractWindow.hpp"
#include "AbstractSubAppFactory.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetworkRepository;

	class SimulatorFactory : public AbstractSubAppFactory
	{
	protected:
		NeuralNetworkRepository* neuralNetworkRepository;
	public:
		SimulatorFactory(NeuralNetworkRepository* neuralNetworkRepository_);
		AbstractSubApp* createSupApp(AbstractMainApp* mainApp, AbstractWindow* parent) const override;
		const std::string& getLabel() const override;
	};
}

#endif
