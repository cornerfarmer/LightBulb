#pragma once

#ifndef _NEURALNETWORKIO_H_
#define _NEURALNETWORKIO_H_

// Includes
#include <vector>
#include <map>

// Forward declarations

// This class contains all stuff needed to describe a NeuralNetworkIO
template<typename T>
class NeuralNetworkIO : public std::map<int, std::vector<T>>
{
public:
	// Unfolds the NeuralNetworkIO into a NeuralNetworkIO with a single time step
	NeuralNetworkIO<T>* unfold()
	{
		// Create a new neuralNetworkIO with one timestep
		NeuralNetworkIO<T>* unfoldedNetworkIO = new NeuralNetworkIO<T>();
		(*unfoldedNetworkIO)[0] = std::vector<T>();
		// Go through all ioSeries in the various timesteps
		for (NeuralNetworkIO<T>::iterator ioSeries = begin(); ioSeries != end(); ioSeries++)
		{
			// Add them at the end of the first timestep
			(*unfoldedNetworkIO)[0].insert((*unfoldedNetworkIO)[0].end(), ioSeries->second.begin(), ioSeries->second.end());
		}
		return unfoldedNetworkIO;
	}

	// Returns the biggest timestep used in this IO
	int getMaxTimeStep()
	{
		return rbegin()->first;
	}
};

#endif