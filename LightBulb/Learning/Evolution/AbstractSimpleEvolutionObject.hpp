#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONOBJECT_H_
#define _ABSTRACTSIMPLEEVOLUTIONOBJECT_H_

// Library Includes
#include <memory>

// Includes
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class RecurrentFeedForwardNetworkTopologyOptions;
	class AbstractEvolutionWorld;
	class AbstractNeuronDescriptionFactory;
	struct FeedForwardNetworkTopologyOptions;

	// This class is simplification of the AbstractEvolutionObject class.
	// It decreases the work you have to do for your evolutionObject class, but also decreases your possibilities.
	// Nevertheless this class can be used in the most of all cases.
	class AbstractSimpleEvolutionObject : public AbstractEvolutionObject
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractSimpleEvolutionObject const& object);
		template <class Archive>
		friend void load(Archive& archive, AbstractSimpleEvolutionObject& object);
	private:
		std::vector<double> lastOutput;
		std::vector<double> lastInput;

		void buildOutputBuffer();
	protected:
		// The NN of the object
		std::unique_ptr<NeuralNetwork> neuralNetwork;
		// The world which holds this object
		AbstractEvolutionWorld* world;
		// This method should return the input for the neural network
		virtual void getNNInput(std::vector<double>& input) = 0;
		// This method should interpret and act depending on the given NN output
		virtual void interpretNNOutput(std::vector<double>& output) = 0;

		void buildNeuralNetwork(FeedForwardNetworkTopologyOptions &options);
	public:
		// Create a new evolution object with the given input and output NN size
		AbstractSimpleEvolutionObject(AbstractEvolutionWorld& world);
		AbstractSimpleEvolutionObject() = default;
		// Inherited:
		void doNNCalculation() override;
		AbstractNeuralNetwork& getNeuralNetwork() override;
		void resetNN() override;
		AbstractEvolutionObject* clone(bool addToWorld = true) const override;
	};
}

#include "IO/AbstractSimpleEvolutionObjectIO.hpp"

#endif
