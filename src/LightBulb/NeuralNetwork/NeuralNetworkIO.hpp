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
	 */
	template<typename T>
	class NeuralNetworkIO : public std::vector<std::pair<bool, T>>
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
			: std::vector<std::pair<bool, T>>(d)
		{
			dimension = d;
		}

		/**
		 * \brief Returns the value of the neuron with the given index
		 * \param index The neuron index.
		 * \return The value.
		 */
		const T& get(int index) const
		{
			// Make sure the value is valid
			if ((*this)[index].first)
				return (*this)[index].second;
			else
				throw std::logic_error("There is no valid value in the given index.");
		}

		/**
		 * \brief Sets the value of the neuron with the given index.
		 * \param index The index.
		 * \param value The new value.
		 */
		void set(int index, T value)
		{
			// Make sure the index is set to valid
			if (!(*this)[index].first)
				(*this)[index].first = true;
			// Finally set the value
			(*this)[index].second = value;
		}

		/**
		 * \brief Returns if the value of the neuron with the given index is valid.
		 * \param index The neuron index.
		 * \return True, if a value exists.
		 */
		bool exists(int index) const
		{
			return ((*this)[index].first);
		}

		/**
		 * \brief Converts the values into a vector (invalid values get the value 0)
		 * \return The vector of values.
		 */
		std::vector<T> getRealVector() const
		{
			std::vector<T> realVector(dimension);
			auto pair = (*this).begin();
			for (auto value = realVector.begin(); value != realVector.end() && pair != (*this).end(); value++, pair++)
			{
				*value = pair->second;
			}
			return realVector;
		}

		/**
		 * \brief Returns the dimension of this NeuralNetworkIO.
		 * \return The dimension.
		 */
		int getDimension() const
		{
			return dimension;
		}

	};
}

#endif
