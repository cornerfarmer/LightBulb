#pragma once

#ifndef _ABSTRACTNETWORKEXPORTER_H_
#define _ABSTRACTNETWORKEXPORTER_H_

// Library includes
#include <string>

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;

	// 
	class AbstractNetworkExporter
	{
	private:
	public:
		virtual ~AbstractNetworkExporter() {}
		virtual std::string getName() const = 0;
		virtual std::string getFileExtensions() const = 0;
		virtual void exportToFile(std::string path, const AbstractNeuralNetwork& neuralNetwork);
		virtual std::string exportToString(const AbstractNeuralNetwork& neuralNetwork) = 0;
	};
}

#endif