#pragma once

#ifndef _BRAINJSEXPORTER_H_
#define _BRAINJSEXPORTER_H_

// Includes
#include "LightBulb/IO/Exporter/AbstractNetworkExporter.hpp"

namespace LightBulb
{
	/**
	 * \brief Exports a neural network for using in BrainJS.
	 */
	class BrainJSExporter : public AbstractNetworkExporter
	{
	private:
	public:
		// Inherited:
		std::string exportToString(const AbstractNeuralNetwork& neuralNetwork) override;
		std::string getName() const override;
		std::string getFileExtensions() const override;
	};
}

#endif