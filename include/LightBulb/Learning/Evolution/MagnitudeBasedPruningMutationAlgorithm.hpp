#pragma once

#ifndef _MAGNITUDEBASEDPRUNINGMUTATIONALGORITHM_H_
#define _MAGNITUDEBASEDPRUNINGMUTATIONALGORITHM_H_

// Library Includes

// Includes
#include "LightBulb/Learning/Evolution/AbstractMutationAlgorithm.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	class EqualRandomFunction;
	/**
	 * \brief A mutation algorithm which removes weights and neurons from given individuals.
	 * \details Removing neurons:\n
	 * Neurons can be choosen by their total efferent weights or their total number of efferent weights.\n
	 * If the random function is activated, the neuron is chosed randomly depending on their weights. Otherwise just the neuron with the lowest weightsum or weight count is taken.\n \n
	 * Removing weights:\n
	 * Weights are choosen by their value. The one with the lowest value is removed.
	 */
	class MagnitudeBasedPruningMutationAlgorithm : public AbstractMutationAlgorithm
	{
	private:
		/**
		 * \brief The random function for choosing the weights and neurons to remove.
		 */
		std::unique_ptr<EqualRandomFunction> randomFunction;
		/**
		 * \brief The amount of neurons to remove.
		 */
		int removeNeuronsPerIteration;
		/**
		 * \brief The amount of weights to remove.
		 */
		int removeWeightsPerIteration;
		/**
		 * \brief True, if neurons should be removed depending on their efferent weights.
		 */
		bool removeNeuronsByTheirTotalWeight;
		/**
		 * \brief True, if a random function should be used for selecting weights and neurons.
		 */
		bool useRandomFunction;
		/**
		 * \brief True, if the input layer should be ignored.
		 */
		bool ignoreInputLayer;
	public:
		/**
		 * \brief Create a magnitude based pruning mutation algorithm.
		 * \param removeNeuronsPerIteration_ The amount of neurons to remove.
		 * \param removeWeightsPerIteration_ The amount of weights to remove.
		 * \param useRandomFunction_ True, if a random function should be used for selecting weights and neurons.
		 * \param ignoreInputLayer_ True, if the input layer should be ignored.
		 * \param removeNeuronsByTheirTotalWeight_ True, if neurons should be removed depending on their efferent weights.
		 */
		MagnitudeBasedPruningMutationAlgorithm(int removeNeuronsPerIteration_, int removeWeightsPerIteration_, bool useRandomFunction_ = true, bool ignoreInputLayer_ = false, bool removeNeuronsByTheirTotalWeight_ = false);
		MagnitudeBasedPruningMutationAlgorithm();
		MagnitudeBasedPruningMutationAlgorithm(MagnitudeBasedPruningMutationAlgorithm&& other) noexcept;
		MagnitudeBasedPruningMutationAlgorithm& operator=(MagnitudeBasedPruningMutationAlgorithm other);

		MagnitudeBasedPruningMutationAlgorithm(const MagnitudeBasedPruningMutationAlgorithm& other);

		friend void swap(MagnitudeBasedPruningMutationAlgorithm& lhs, MagnitudeBasedPruningMutationAlgorithm& rhs) noexcept;
		~MagnitudeBasedPruningMutationAlgorithm();
		// Inherited:
		void execute(AbstractIndividual& individual1) override;
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
