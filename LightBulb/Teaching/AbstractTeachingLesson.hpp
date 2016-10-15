#pragma once

#ifndef _ABSTRACTTEACHINGLESSON_H_
#define _ABSTRACTTEACHINGLESSON_H_

// Library Includes
#include <EigenSrc/Dense>
#include <vector>
#include <map>
#include <memory>

// Includes
#include "NeuralNetwork/NeuralNetworkIO.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	class AbstractActivationOrder;
	class AbstractActivationFunction;
	class AbstractNeuron;
	class StandardNeuron;

	typedef std::vector<Eigen::VectorXd> ErrorMap_t;

	class AbstractTeachingLesson
	{
	public:
		virtual ~AbstractTeachingLesson() {}
		// Put the teachingPattern into the neuralNetwork, refresh the network and fills (optional) the given output and netput values map
		std::vector<std::vector<double>> tryLesson(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = nullptr, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = nullptr) const;
		// This method should return a double vector of the teachingInput 
		virtual const NeuralNetworkIO<double>* getTeachingInput(const AbstractActivationFunction* activationFunction) const = 0;
		// Returns a map of all teaching inputs of all neurons in all timesteps TODO: Discuss if this method makes sense
		std::unique_ptr<ErrorMap_t> getTeachingInputMap(AbstractNeuralNetwork &neuralNetwork) const;
		// This method should return a double vector of the teachingPattern
		virtual const std::vector<std::vector<double>>* getTeachingPattern() const = 0;
		// Calculate the Errormap and fills (optional) the given output and netput values map
		std::unique_ptr<ErrorMap_t> getErrormap(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = nullptr, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = nullptr, bool clipError = false) const;
		// Returns the Errormap from the given output vector
		virtual std::unique_ptr<ErrorMap_t> getErrormapFromOutputVector(const std::vector<std::vector<double>>& outputVector, AbstractNeuralNetwork &neuralNetwork, bool clipError = false) const;
		// Calculate the specific error
		virtual double getSpecificError(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder, bool clipError = false) const;
		// Unfolds the teaching lesson
		virtual AbstractTeachingLesson* unfold() const = 0;
		// Returns the maximal time step in the teaching lesson
		virtual int getMaxTimeStep() const = 0;
	};
}

#endif

