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
		std::vector<std::vector<double>> tryLesson(AbstractNeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = nullptr, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = nullptr);
		// This method should return a double vector of the teachingInput 
		virtual NeuralNetworkIO<double>* getTeachingInput(AbstractActivationFunction* activationFunction) = 0;
		// Returns a map of all teaching inputs of all neurons in all timesteps TODO: Discuss if this method makes sense
		std::unique_ptr<ErrorMap_t> getTeachingInputMap(AbstractNeuralNetwork &neuralNetwork);
		// This method should return a double vector of the teachingPattern
		virtual std::vector<std::vector<double>>* getTeachingPattern() = 0;
		// Calculate the Errormap and fills (optional) the given output and netput values map
		std::unique_ptr<ErrorMap_t> getErrormap(AbstractNeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, std::vector<std::map<AbstractNeuron*, double>>* outputValuesInTime = nullptr, std::vector<std::map<AbstractNeuron*, double>>* netInputValuesInTime = nullptr, bool clipError = false);
		// Returns the Errormap from the given output vector
		virtual std::unique_ptr<ErrorMap_t> getErrormapFromOutputVector(std::vector<std::vector<double>>& outputVector, AbstractNeuralNetwork &neuralNetwork, bool clipError = false);
		// Calculate the specific error
		virtual double getSpecificError(AbstractNeuralNetwork &neuralNetwork, AbstractActivationOrder &activationOrder, bool clipError = false);
		// Unfolds the teaching lesson
		virtual AbstractTeachingLesson* unfold() = 0;
		// Returns the maximal time step in the teaching lesson
		virtual int getMaxTimeStep() = 0;
	};
}

#endif

