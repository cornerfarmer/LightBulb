// Includes
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "TeachingInput.hpp"
// Library includes
#include <math.h>
#include "NeuronDescription/NeuronDescription.hpp"
#include <Eigen/src/Core/util/ForwardDeclarations.h>
#include <memory>

namespace LightBulb
{
	std::vector<double> AbstractTeachingLesson::tryLesson(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder) const
	{
		std::vector<double> output(neuralNetwork.getNetworkTopology().getOutputSize());
		// Let the network calculate
		neuralNetwork.calculate(getTeachingPattern(), output, activationOrder);
		return output;
	}

	std::unique_ptr<Eigen::VectorXd> AbstractTeachingLesson::getErrorVector(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder, bool clipError) const
	{
		std::unique_ptr<Eigen::VectorXd> errorVector;

		// Try the lesson and extract the output
		std::vector<double> outputVector = tryLesson(neuralNetwork, activationOrder);
		errorVector = getErrorVectorFromOutputVector(outputVector, neuralNetwork, clipError);

		return errorVector;
	}


	std::unique_ptr<Eigen::VectorXd> AbstractTeachingLesson::getErrorVectorFromOutputVector(const std::vector<double>& outputVector, AbstractNeuralNetwork& neuralNetwork, bool clipError) const
	{
		// Get the teachingInput
		const TeachingInput<double>& teachingInput = getTeachingInput(neuralNetwork.getNetworkTopology().getOutputNeuronDescription().getActivationFunction());

		// Create the errorVector
		std::unique_ptr<Eigen::VectorXd> errorVector(new Eigen::VectorXd(teachingInput.getDimension()));

		// Calculate the error values (expected value - real value)
		for (int i = 0; i < teachingInput.getDimension(); i++)
		{
			if (teachingInput.exists(i))
			{
				(*errorVector)[i] = teachingInput.get(i) - outputVector[i];
				if (clipError)
					(*errorVector)[i] = std::max(-1.0, std::min(1.0, (*errorVector)[i]));
			}
			else
				(*errorVector)[i] = 0;
		}

		return errorVector;
	}


	double AbstractTeachingLesson::getSpecificError(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder, bool clipError) const
	{
		// Calculate the errorVector
		std::unique_ptr<Eigen::VectorXd> errorVector = getErrorVector(neuralNetwork, activationOrder, clipError);

		double specificError = 0;

		// Add the square of every errorValue in the errorVector
		for (int i = 0; i < errorVector->rows(); i++)
		{
			specificError += pow((*errorVector)(i), 2.0);
		}		

		// Divide the specific error by two
		specificError /= 2;

		return specificError;
	}

}
