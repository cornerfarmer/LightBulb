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
	// Holds the dimension (amount of neurons the NeuralNetworkIO can describe)
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
		for (auto ioSeries = this->begin(); ioSeries != this->end(); ioSeries++)
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
		if (!this->empty())
			return this->size() - 1;
		else
			return 0;
	}

	// Returns the value of the neuron with the given index in the given timestep
	T& get(int timestep, int index)
	{
		// Make sure the value is valid
		if ((*this)[timestep].first && (*this)[timestep].second[index].first)
			return (*this)[timestep].second[index].second;
		else
			throw new std::logic_error("There is no valid value in the given timestep with the given timestep.");
	}

	// Sets the value of the neuron with the given index in the given timestep
	void set(int timestep, int index, T value)
	{
		// Resize the vector if necessary
		if (this->size() <= timestep)
			this->resize(timestep + 1, std::pair<bool, std::vector<std::pair<bool, T>>>(false, std::vector<std::pair<bool, T>>(dimension)));
		// Make sure the timestep is set to valid
		if (!(*this)[timestep].first)
			(*this)[timestep].first = true;
		// Make sure the index is set to valid
		if (!(*this)[timestep].second[index].first)
			(*this)[timestep].second[index].first = true;
		// Finally set the value
		(*this)[timestep].second[index].second = value;
	}

	// Sets all values at the given timestep
	void set(int timestep, std::vector<std::pair<bool, T>> values)
	{
		// Resize the vector if necessary
		if (this->size() <= timestep)
			this->resize(timestep + 1, std::pair<bool, std::vector<std::pair<bool, T>>>(false, std::vector<std::pair<bool, T>>(dimension)));
		// Make sure the timestep is set to valid
		if (!(*this)[timestep].first)
			(*this)[timestep].first = true;
		// Finally set the values
		(*this)[timestep].second = values;		
	}

	// Returns if the value of the neuron with the given index in the given timestep is valid
	bool exists(int timestep, int index)
	{
		return (this->size() > timestep && (*this)[timestep].second[index].first);
	}

	// Returns if the given timestep has at least one valid value
	bool existsTimestep(int timestep)
	{
		return (this->size() > timestep && (*this)[timestep].first);
	}

	// Converts the values of a timestep into a vector (invalid values get the value 0)
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

	// Returns the dimension of the io
	int getDimension()
	{
		return dimension;
	}

};

#endif
