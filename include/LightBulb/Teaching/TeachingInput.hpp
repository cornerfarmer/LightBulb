#pragma once

#ifndef _TEACHINGINPUT_H_
#define _TEACHINGINPUT_H_

// Includes
#include <vector>
#include <map>

namespace LightBulb
{
	/**
	 * \brief This class contains all stuff needed to describe what a network should return.
	 * \tparam T The data type which should be used.
	 */
	template<typename T = float>
	class TeachingInput
	{
	private:
		Vector<T> values;
		Vector<char> enabled;
	public:

		/**
		 * \brief Creates a new NeuralNetworkIO
		 * \param d The dimension which should be equal to the output neurons of the corresponding network.
		 */
		TeachingInput(int d)
			: values(d), enabled(d)
		{
			enabled.getEigenValueForEditing().setZero();
		}

		/**
		 * \brief Returns the value of the neuron with the given index
		 * \param index The neuron index.
		 * \return The value.
		 */
		const T& get(int index) const
		{
			// Make sure the value is valid
			if (enabled.getEigenValue()[index])
				return values.getEigenValue()[index];
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
			if (!enabled.getEigenValue()[index])
				enabled.getEigenValueForEditing()[index] = true;
			// Finally set the value
			values.getEigenValueForEditing()[index] = value;
		}

		/**
		 * \brief Returns if the value of the neuron with the given index is valid.
		 * \param index The neuron index.
		 * \return True, if a value exists.
		 */
		bool exists(int index) const
		{
			return enabled.getEigenValue()[index];
		}

		void clear()
		{
			enabled.getEigenValueForEditing().setZero();
		}

		Vector<T>& getValues()
		{
			return values;
		}

		Vector<char>& getEnabled()
		{
			return enabled;
		}

		const Vector<T>& getValues() const
		{
			return values;
		}

		const Vector<char>& getEnabled() const
		{
			return enabled;
		}

		/**
		* \brief Returns the dimension of this NeuralNetworkIO.
		* \return The dimension.
		*/
		int getDimension() const
		{
			return values.getEigenValue().size();
		}

		bool operator==(const TeachingInput<T>& other) const
		{
			return values == other.values && enabled == other.enabled;
		}
	};
}

#endif
