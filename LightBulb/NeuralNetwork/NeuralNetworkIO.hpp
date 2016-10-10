#pragma once

#ifndef _NEURALNETWORKIO_H_
#define _NEURALNETWORKIO_H_

// Includes
#include <vector>
#include <map>

namespace LightBulb
{
	/**
	 * \brief This class contains all stuff needed to describe the input and output of a neural network.
	 * \tparam T The data type which should be used.
	 * TODO: Refactor!
	 */
	template<typename T>
	class NeuralNetworkIO : public std::vector<std::pair<bool, std::vector<std::pair<bool, T>>>>
	{
	private:
		/**
		 * \brief Contains the dimension (amount of neurons the NeuralNetworkIO can describe)
		 */
		int dimension;
	public:

		/**
		 * \brief Creates a new NeuralNetworkIO
		 * \param d The dimension which should be equal to the output neurons of the corresponding network.
		 */
		NeuralNetworkIO(int d)
			: std::vector<std::pair<bool, std::vector<std::pair<bool, T>>>>(1, std::pair<bool, std::vector<std::pair<bool, T>>>(false, std::vector<std::pair<bool, T>>(d)))
		{
			dimension = d;
		}

		/**
		 * \brief Unfolds the NeuralNetworkIO into a NeuralNetworkIO with a single time step
		 * \return The unfolded NeuralNetworkIO
		 */
		NeuralNetworkIO<T>* unfold()
		{
			// Create a new neuralNetworkIO with one timestep
			NeuralNetworkIO<T>* unfoldedNetworkIO = new NeuralNetworkIO<T>(0);
			unfoldedNetworkIO->set(0, std::vector<std::pair<bool, T>>());
			// Go through all ioSeries in the various timesteps
			for (auto ioSeries = this->begin(); ioSeries != this->end(); ioSeries++)
			{
				// Add them at the end of the first timestep
				(*unfoldedNetworkIO)[0].second.insert((*unfoldedNetworkIO)[0].second.end(), ioSeries->second.begin(), ioSeries->second.end());
			}
			unfoldedNetworkIO->dimension = (*unfoldedNetworkIO)[0].second.size();
			return unfoldedNetworkIO;
		}

		/**
		 * \brief Returns the biggest timestep used in this IO
		 * \return The maximal timestep.
		 */
		int getMaxTimeStep()
		{
			if (!this->empty())
				return this->size() - 1;
			else
				return 0;
		}

		/**
		 * \brief Returns the value of the neuron with the given index in the given timestep
		 * \param timestep The timestep.
		 * \param index The neuron index.
		 * \return The value.
		 */
		T& get(int timestep, int index)
		{
			// Make sure the value is valid
			if ((*this)[timestep].first && (*this)[timestep].second[index].first)
				return (*this)[timestep].second[index].second;
			else
				throw new std::logic_error("There is no valid value in the given timestep with the given timestep.");
		}

		/**
		 * \brief Sets the value of the neuron with the given index in the given timestep.
		 * \param timestep The timestep.
		 * \param index The index.
		 * \param value The new value.
		 */
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

		/**
		 * \brief Sets all values at the given timestep.
		 * \param timestep The timestep.
		 * \param values A vector of values
		 */
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

		/**
		 * \brief Returns if the value of the neuron with the given index in the given timestep is valid.
		 * \param timestep The timestep.
		 * \param index The neuron index.
		 * \return True, if a value exists.
		 */
		bool exists(int timestep, int index)
		{
			return (this->size() > timestep && (*this)[timestep].second[index].first);
		}

		/**
		 * \brief Returns if the given timestep has at least one valid value.
		 * \param timestep The timestep.
		 * \return True, if the timestep exists.
		 */
		bool existsTimestep(int timestep)
		{
			return (this->size() > timestep && (*this)[timestep].first);
		}

		/**
		 * \brief Converts the values of a timestep into a vector (invalid values get the value 0)
		 * \param timestep The timestep.
		 * \return The vector of values at this timestep.
		 */
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

		/**
		 * \brief Returns the real values of al timesteps.
		 * \return A vector of all timestep vectors.
		 */
		std::vector<std::vector<T>> getRealVector()
		{
			std::vector<std::vector<T>> realVector(this->size());
			for (int t = 0; t < realVector.size(); t++)
			{
				realVector[t] = getRealVectorInTimestep(t);
			}
			return realVector;
		}

		/**
		 * \brief Returns the dimension of this NeuralNetworkIO.
		 * \return The dimension.
		 */
		int getDimension()
		{
			return dimension;
		}

	};
}

#endif
