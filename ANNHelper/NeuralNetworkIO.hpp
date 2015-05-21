#pragma once

#ifndef _NEURALNETWORKIO_H_
#define _NEURALNETWORKIO_H_

// Includes
#include <vector>
#include <list>

// Forward declarations


// This class contains all stuff needed to describe a NeuralNetwork
class NeuralNetworkIO : public std::list<std::vector<float>>
{
public:
	NeuralNetworkIO* unfold();
};

#endif