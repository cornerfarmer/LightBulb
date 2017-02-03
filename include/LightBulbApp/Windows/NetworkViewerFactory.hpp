#pragma once

#ifndef _NETWORKVIEWERFACTORY_H_
#define _NETWORKVIEWERFACTORY_H_

// Includes
#include "AbstractSubAppFactory.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetworkRepository;
	/**
	* \brief A factory for the network viewer sub app.
	*/
	class NetworkViewerFactory : public AbstractSubAppFactory
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
		NetworkViewerFactory(NeuralNetworkRepository& neuralNetworkRepository_);
		// Inherited:
		AbstractSubApp* createSupApp(AbstractMainApp& mainApp, AbstractWindow& parent) const override;
		std::string getLabel() const override;
	};
}

#endif
