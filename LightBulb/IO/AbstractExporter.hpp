#pragma once

#ifndef _ABSTRACTEXPORTER_H_
#define _ABSTRACTEXPORTER_H_

// Library includes
#include <string>

// Forward declarations
class NeuralNetwork;

// 
class AbstractExporter
{
private:
public:
	virtual std::string execute(NeuralNetwork* neuralNetwork) = 0;
};

#endif