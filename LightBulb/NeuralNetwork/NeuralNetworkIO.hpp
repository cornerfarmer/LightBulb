#pragma once

#ifndef _NEURALNETWORKIO_H_
#define _NEURALNETWORKIO_H_

// Includes
#include <vector>
#include <map>

// Forward declarations

// This class contains all stuff needed to describe a NeuralNetworkIO
template<typename T>
class NeuralNetworkIO : public std::vector<std::pair<bool, std::vector<std::pair<bool, T>>>>
{
private:
	int dimension;
public:
	NeuralNetworkIO(int d)
	{
		dimension = d;
	}

	// Unfolds the NeuralNetworkIO into a NeuralNetworkIO with a single time step
	NeuralNetworkIO<T>* unfold()
	{
		// Create a new neuralNetworkIO with one timestep
		NeuralNetworkIO<T>* unfoldedNetworkIO = new NeuralNetworkIO<T>(0);
		unfoldedNetworkIO->set(0, std::vector<std::pair<bool,T>>());
		// Go through all ioSeries in the various timesteps
		for (auto ioSeries = begin(); ioSeries != end(); ioSeries++)
		{			
			// Add them at the end of the first timestep
			(*unfoldedNetworkIO)[0].second.insert((*unfoldedNetworkIO)[0].second.end(), ioSeries->second.begin(), ioSeries->second.end());
		}
		unfoldedNetworkIO->dimension = (*unfoldedNetworkIO)[0].second.size();
		return unfoldedNetworkIO;
	}

	// Returns the biggest timestep used in this IO
	int getMaxTimeStep()
	{
		if (!empty())
			return size() - 1;
		else
			return 0;
	}

	T& get(int timestep, int index)
	{
		if ((*this)[timestep].first && (*this)[timestep].second[index].first)
			return (*this)[timestep].second[index].second;
		else
			throw new std::logic_error("");
	}

	void set(int timestep, int index, T value)
	{
		if (size() <= timestep)
			resize(timestep + 1, std::pair<bool, std::vector<std::pair<bool, T>>>(false, std::vector<std::pair<bool, T>>(dimension)));
		if (!(*this)[timestep].first)
			(*this)[timestep].first = true;
		if (!(*this)[timestep].second[index].first)
			(*this)[timestep].second[index].first = true;
		(*this)[timestep].second[index].second = value;
	}
	void resizeToTimestep(int timestep)
	{
		if (size() <= timestep)
			resize(timestep + 1, std::pair<bool, std::vector<std::pair<bool, T>>>(false, std::vector<std::pair<bool, T>>(dimension)));
		if (!(*this)[timestep].first)
			(*this)[timestep].first = true;
	}
	void set(int timestep, std::vector<std::pair<bool, T>> values)
	{
		if (size() <= timestep)
			resize(timestep + 1, std::pair<bool, std::vector<std::pair<bool, T>>>(false, std::vector<std::pair<bool, T>>(dimension)));
		if (!(*this)[timestep].first)
			(*this)[timestep].first = true;
		(*this)[timestep].second = values;		
	}

	bool exists(int timestep, int index)
	{
		return (size() > timestep && (*this)[timestep].second[index].first);
	}

	bool existsTimestep(int timestep)
	{
		return (size() > timestep && (*this)[timestep].first);
	}


	std::vector<T> getRealVectorInTimestep(int timestep)
	{
		std::vector<T> realVector(dimension);
		auto pair = (*this)[timestep].second.begin();
		for (auto value = realVector.begin(); value != realVector.end() && pair != (*this)[timestep].second.end(); value++, pair++)
		{
			*value = pair->second;
		}		
		return realVector;
	}

	int getDimension()
	{
		return dimension;
	}

};

#endif