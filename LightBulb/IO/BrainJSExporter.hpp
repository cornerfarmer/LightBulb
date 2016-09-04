#pragma once

#ifndef _BRAINJSEXPORTER_H_
#define _BRAINJSEXPORTER_H_

// Includes
#include "IO/AbstractExporter.hpp"

// Forward declarations

// 
class BrainJSExporter : public AbstractExporter
{
private:
public:
	std::string execute(NeuralNetwork* neuralNetwork) override;
};

#endif