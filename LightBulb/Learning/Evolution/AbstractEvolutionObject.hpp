#pragma once

#ifndef _AbstractEvolutionObject_H_
#define _AbstractEvolutionObject_H_

// Library includes
#include <vector>
#include <algorithm>
#include "Random/AbstractRandomGeneratorUser.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class AbstractNeuralNetwork;
	/**
	 * \brief All evolution methods which can be source of evolution objects.
	 */
	enum EvolutionSource
	{
		Creation,
		Mutation,
		Recombination,
		Reuse
	};
	/**
	 * \brief This class describes an abstract object which "lives" inside an evolution world.
	 * \details The evolution object contains a NN which should calculate the actions from external and internal inputs.
	 */
	class AbstractEvolutionObject
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractEvolutionObject const& object);
		template <class Archive>
		friend void load(Archive& archive, AbstractEvolutionObject& object);
	protected:
		/**
		 * \brief This vector describes the mutation strength of every edge in the NN.
		 * \details It is mostly used inside the mutation/recombination algorithms.
		 */
		std::vector<double> mutationStrength;
		/**
		 * \brief Contains the evolution method which has been the origin of this object.
		 */
		EvolutionSource evolutionSource;
		/**
		 * \brief Resizes the mutation strength vector.
		 * \param newSize The new size.
		 */
		void resizeMutationStrength(int newSize);
		/**
		 * \brief Randomizes all values inside the mutation strength vecor
		 */
		void randomizeMutationStrength();
	public:
		virtual ~AbstractEvolutionObject() {}
		/**
		 * \brief Copies all properties from the given object.
		 * \details Copies the network and the mutation strengths.
		 * \param notUsedObject The object which should be copied.
		 */
		virtual void copyPropertiesFrom(AbstractEvolutionObject& notUsedObject);
		/**
		 * \brief Returns the neural network.
		 * \return The neural network.
		 */
		virtual AbstractNeuralNetwork& getNeuralNetwork() = 0;
		/**
		 * \brief Returns the mutation strength.
		 * \return The mutation strength.
		 */
		virtual std::vector<double>& getMutationStrength();
		/**
		* \brief Returns the mutation strength.
		* \return The mutation strength.
		*/
		const std::vector<double>& getMutationStrength() const;
		/**
		 * \brief Sets the mutation strength.
		 * \param newMutationStrength The new mutation strength to use.
		 */
		virtual void setMutationStrength(const std::vector<double>& newMutationStrength);
		/**
		 * \brief Executes one NN calculation. (Mostly: Get input -> let the NN calculate -> react depending on the NN output)
		 */
		virtual void doNNCalculation() = 0;
		/**
		 * \brief Resets the NN (All activations to zero)
		 */
		virtual void resetNN() = 0;
		/**
		 * \brief Clones the evolution object.
		 * \details Creates a new object with a cloned neural network and the same mutation strengths.
		 * \param addToWorld Set to true, if the new object should be added to the evolution world.
		 * \return The new object.
		 */
		virtual AbstractEvolutionObject* clone(bool addToWorld = true) const = 0;
		/**
		 * \brief Sets the evolution source of the object.
		 * \param evolutionSource_ The new evolution source.
		 */
		virtual void setEvolutionSource(const EvolutionSource& evolutionSource_);
		/**
		 * \brief Returns the evolution method which has been the origin of this object.
		 * \return The evolution source.
		 */
		const EvolutionSource& getEvolutionSource() const;
		/**
		 * \brief Removes a neuron from the internal neural network.
		 * \param layerIndex The index of the layer.
		 * \param neuronIndex The index of the neuron in the layer.
		 */
		virtual void removeNeuron(int layerIndex, int neuronIndex);
		/**
		 * \brief Adds a new neuron to the internal network-
		 * \param layerIndex The index of the layer where to add the new neuron.
		 */
		virtual void addNeuron(int layerIndex);
	};
}

#include "IO/AbstractEvolutionObjectIO.hpp"

#endif
