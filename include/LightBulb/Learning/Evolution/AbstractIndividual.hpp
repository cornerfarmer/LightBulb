#pragma once

#ifndef _ABSTRACTINDIVIDUAL_H_
#define _ABSTRACTINDIVIDUAL_H_

// Library includes
#include "LightBulb/LinearAlgebra/AbstractLinearAlgebraUser.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class AbstractNeuralNetwork;
	/**
	 * \brief All evolution methods which can be source of individuals.
	 */
	enum EvolutionSource : unsigned int
	{
		Creation,
		Mutation,
		Recombination,
		Reuse
	};
	/**
	 * \brief This class describes an abstract individual which "lives" inside an evolution environment.
	 * \details The individual contains a NN which should calculate the actions from external and internal inputs.
	 */
	class AbstractIndividual : public virtual AbstractLinearAlgebraUser
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractIndividual const& individual);
		template <class Archive>
		friend void load(Archive& archive, AbstractIndividual& individual);
	protected:
		/**
		 * \brief This vector describes the mutation strength of every edge in the NN.
		 * \details It is mostly used inside the mutation/recombination algorithms.
		 */
		Vector<> mutationStrength;
		/**
		 * \brief Contains the evolution method which has been the origin of this individual.
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
		virtual ~AbstractIndividual() {}
		/**
		 * \brief Copies all properties from the given individual.
		 * \details Copies the network and the mutation strengths.
		 * \param notUsedIndividual The individual which should be copied.
		 */
		virtual void copyPropertiesFrom(AbstractIndividual& notUsedIndividual);
		/**
		 * \brief Returns the neural network.
		 * \return The neural network.
		 */
		virtual AbstractNeuralNetwork& getNeuralNetwork() = 0;
		/**
		 * \brief Returns the mutation strength.
		 * \return The mutation strength.
		 */
		virtual Vector<>& getMutationStrength();
		/**
		* \brief Returns the mutation strength.
		* \return The mutation strength.
		*/
		const Vector<>& getMutationStrength() const;
		/**
		 * \brief Sets the mutation strength.
		 * \param newMutationStrength The new mutation strength to use.
		 */
		virtual void setMutationStrength(const Vector<>& newMutationStrength);
		/**
		 * \brief Executes one NN calculation. (Mostly: Get input -> let the NN calculate -> react depending on the NN output)
		 */
		virtual void doNNCalculation() = 0;
		/**
		 * \brief Resets the NN (All activations to zero)
		 */
		virtual void resetNN() = 0;
		/**
		 * \brief Clones the individual.
		 * \details Creates a new individual with a cloned neural network and the same mutation strengths.
		 * \param addToEnvironment Set to true, if the new individual should be added to the evolution environment.
		 * \return The new individual.
		 */
		virtual AbstractIndividual* clone(bool addToEnvironment = true) const = 0;
		/**
		 * \brief Sets the evolution source of the individual.
		 * \param evolutionSource_ The new evolution source.
		 */
		virtual void setEvolutionSource(const EvolutionSource& evolutionSource_);
		/**
		 * \brief Returns the evolution method which has been the origin of this individual.
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
		// Inherited:
		void setCalculatorType(const CalculatorType& calculatorType) override;
	};
}

#include "LightBulb/IO/AbstractIndividualIO.hpp"

#endif
