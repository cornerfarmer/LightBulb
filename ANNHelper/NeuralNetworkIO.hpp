#pragma once

#ifndef _NEURALNETWORKIO_H_
#define _NEURALNETWORKIO_H_

// Includes
#include <vector>
#include <map>

// Forward declarations

// This class contains all stuff needed to describe a NeuralNetwork
template<typename T>
class NeuralNetworkIO : public std::map<int, std::vector<T>>
{
public:
	NeuralNetworkIO<T>* unfold()
	{
		NeuralNetworkIO<T>* unfoldedNetworkIO = new NeuralNetworkIO<T>();
		(*unfoldedNetworkIO)[0] = std::vector<T>();
		for (NeuralNetworkIO<T>::iterator ioSeries = begin(); ioSeries != end(); ioSeries++)
		{
			(*unfoldedNetworkIO)[0].insert((*unfoldedNetworkIO)[0].end(), ioSeries->second.begin(), ioSeries->second.end());
		}
		return unfoldedNetworkIO;
	}

	int getMaxTimeStep()
	{
		return rbegin()->first;
	}
};

#endif