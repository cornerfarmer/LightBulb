#pragma once

#ifndef _BRAINJSEXPORTER_H_
#define _BRAINJSEXPORTER_H_

// Includes
#include "IO/AbstractNetworkExporter.hpp"

namespace LightBulb
{
	// Forward declarations

	// 
	class BrainJSExporter : public AbstractNetworkExporter
	{
	private:
	public:
		std::string exportToString(const AbstractNeuralNetwork& neuralNetwork) override;
		std::string getName() const override;
		std::string getFileExtensions() const override;
	};
}

#endif