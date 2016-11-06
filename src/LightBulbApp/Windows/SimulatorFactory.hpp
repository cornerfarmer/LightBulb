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
	/**
	* \brief A factory for the simulator sub app.
	*/
	class SimulatorFactory : public AbstractSubAppFactory
	{
	protected:
		/**
		* \brief The neural network repository to use.
		*/
		NeuralNetworkRepository* neuralNetworkRepository;
	public:
		/**
		* \brief Creates the factory.
		* \param neuralNetworkRepository_ The neural network repository to use.
		*/
		SimulatorFactory(NeuralNetworkRepository& neuralNetworkRepository_);
		// Inherited:
		AbstractSubApp* createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const override;
		std::string getLabel() const override;
	};
}

#endif
