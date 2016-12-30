// Includes
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/Teaching/TeachingInput.hpp"
// Library includes
#include <math.h>
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
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

	std::unique_ptr<Vector> AbstractTeachingLesson::getErrorVector(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder, bool clipError) const
	{
		std::unique_ptr<Vector> errorVector;

		// Try the lesson and extract the output
		std::vector<double> outputVector = tryLesson(neuralNetwork, activationOrder);
		errorVector = getErrorVectorFromOutputVector(outputVector, neuralNetwork, clipError);

		return errorVector;
	}


	std::unique_ptr<Vector> AbstractTeachingLesson::getErrorVectorFromOutputVector(const std::vector<double>& outputVector, AbstractNeuralNetwork& neuralNetwork, bool clipError) const
	{
		// Get the teachingInput
		const TeachingInput<double>& teachingInput = getTeachingInput(neuralNetwork.getNetworkTopology().getOutputNeuronDescription().getActivationFunction());

		// Create the errorVector
		std::unique_ptr<Vector> errorVector(new Vector(teachingInput.getDimension()));

		// Calculate the error values (expected value - real value)
		if (errorVector->getCalculatorType() == CT_GPU)
		{
			for (int i = 0; i < teachingInput.getDimension(); i++)
			{
				if (teachingInput.exists(i))
				{
					(*errorVector).getViennaclValueForEditing()[i] = teachingInput.get(i) - outputVector[i];
					if (clipError)
						throw std::logic_error("Not implemented yet.");
				}
				else
					(*errorVector).getViennaclValueForEditing()[i] = 0;
			}
		}
		else
		{
			for (int i = 0; i < teachingInput.getDimension(); i++)
			{
				if (teachingInput.exists(i))
				{
					(*errorVector).getEigenValueForEditing()[i] = teachingInput.get(i) - outputVector[i];
					if (clipError)
						(*errorVector).getEigenValueForEditing()[i] = std::max(-1.0f, std::min(1.0f, (*errorVector).getEigenValue()[i]));
				}
				else
					(*errorVector).getEigenValueForEditing()[i] = 0;
			}
		}
		return errorVector;
	}


	double AbstractTeachingLesson::getSpecificError(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder, bool clipError) const
	{
		// Calculate the errorVector
		std::unique_ptr<Vector> errorVector = getErrorVector(neuralNetwork, activationOrder, clipError);

		double specificError = 0;

		if (errorVector->getCalculatorType() == CT_GPU) 
		{
			viennacl::scalar<float> sum = 0;
			viennacl::vector<float> pow = viennacl::scalar_vector<float>((*errorVector).getViennaclValue().size(), 2.0f);
			viennacl::linalg::sum_impl(viennacl::linalg::element_pow((*errorVector).getViennaclValue(), pow), sum);
			specificError = sum;
		}
		else
		{
			// Add the square of every errorValue in the errorVector
			for (int i = 0; i < errorVector->getEigenValue().rows(); i++)
			{
				specificError += pow((*errorVector).getEigenValue()(i), 2.0);
			}
		}

		// Divide the specific error by two
		specificError /= 2;

		return specificError;
	}

}
