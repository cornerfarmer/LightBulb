#pragma once

#ifndef _ABSTRACTEXPORTER_H_
#define _ABSTRACTEXPORTER_H_

// Library includes
#include <string>

namespace LightBulb
{
	// Forward declarations
	class NeuralNetwork;

	// 
	class AbstractExporter
	{
	private:
	public:
		virtual ~AbstractExporter() {};
		virtual std::string execute(NeuralNetwork* neuralNetwork) = 0;
	};
}

#endif