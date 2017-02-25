// Includes
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/Teaching/TeachingInput.hpp"
// Library includes
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"

namespace LightBulb
{
	AbstractTeachingLesson::AbstractTeachingLesson()
	{
		calcErrorVectorKernel.reset(new Kernel("teaching_lesson", "calc_error_vector"));
		calcSpecificErrorKernel.reset(new Kernel("teaching_lesson", "calc_specific_error"));
	}

	AbstractTeachingLesson::~AbstractTeachingLesson() = default;

	const Vector<>& AbstractTeachingLesson::tryLesson(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder) const
	{
		return neuralNetwork.calculateWithoutOutputCopy(getTeachingPattern(), activationOrder);
	}

	const Vector<>& AbstractTeachingLesson::getErrorVector(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder, bool clipError) const
	{
		// Try the lesson and extract the output
		const Vector<>& outputVector = tryLesson(neuralNetwork, activationOrder);
		getErrorVectorFromOutputVector(outputVector, neuralNetwork, clipError);

		return errorVector;
	}


	void AbstractTeachingLesson::getErrorVectorFromOutputVector(const Vector<>& outputVector, AbstractNeuralNetwork& neuralNetwork, bool clipError) const
	{
		// Get the teachingInput
		const TeachingInput<>& teachingInput = getTeachingInput(neuralNetwork.getNetworkTopology().getOutputNeuronDescription().getActivationFunction());

		// Create the errorVector
		//std::unique_ptr<Vector> errorVector(new Vector(teachingInput.getDimension()));

		// Calculate the error values (expected value - real value)
		if (isCalculatorType(CT_GPU))
		{
			if (errorVector.getViennaclValue().size() != teachingInput.getValues().getViennaclValue().size()) {
				errorVector.getViennaclValueForEditing().resize(teachingInput.getValues().getViennaclValue().size());
			}
			
			calcErrorVector(errorVector.getViennaclValueForEditing(), teachingInput.getValues().getViennaclValue(), teachingInput.getEnabled().getViennaclValue(), outputVector.getViennaclValue());
		}
		else
		{
			if (errorVector.getEigenValue().size() != teachingInput.getValues().getEigenValue().size()) {
				errorVector.getEigenValueForEditing().resize(teachingInput.getValues().getEigenValue().size());
			}

			for (int i = 0; i < teachingInput.getDimension(); i++)
			{
				if (teachingInput.exists(i))
				{
					errorVector.getEigenValueForEditing()[i] = teachingInput.get(i) - outputVector.getEigenValue()[i];
					if (clipError)
						errorVector.getEigenValueForEditing()[i] = std::max(-1.0f, std::min(1.0f, errorVector.getEigenValue()[i]));
				}
				else
					errorVector.getEigenValueForEditing()[i] = 0;
			}
		}
	}

	void AbstractTeachingLesson::calcErrorVector(viennacl::vector<float>& errorVector, const viennacl::vector<float>& teachingInput, const viennacl::vector<char>& teachingInputEnabled, const viennacl::vector<float>& outputVector) const
	{
		viennacl::ocl::enqueue(calcErrorVectorKernel->use()(
			viennacl::traits::opencl_handle(errorVector),
			cl_uint(viennacl::traits::start(errorVector)),
			cl_uint(viennacl::traits::stride(errorVector)),
			cl_uint(viennacl::traits::size(errorVector)),

			viennacl::traits::opencl_handle(teachingInput),
			cl_uint(viennacl::traits::start(teachingInput)),
			cl_uint(viennacl::traits::stride(teachingInput)),

			viennacl::traits::opencl_handle(teachingInputEnabled),
			cl_uint(viennacl::traits::start(teachingInputEnabled)),
			cl_uint(viennacl::traits::stride(teachingInputEnabled)),

			viennacl::traits::opencl_handle(outputVector),
			cl_uint(viennacl::traits::start(outputVector)),
			cl_uint(viennacl::traits::stride(outputVector))
		));
	}


	double AbstractTeachingLesson::getSpecificError(AbstractNeuralNetwork& neuralNetwork, const AbstractActivationOrder& activationOrder, bool clipError) const
	{
		// Calculate the errorVector
		getErrorVector(neuralNetwork, activationOrder, clipError);

		double specificError = 0;

		if (isCalculatorType(CT_GPU))
		{
			calcSpecificError(specificErrorScalar.getViennaclValueForEditing(), errorVector.getViennaclValueForEditing());
			specificError = specificErrorScalar.getViennaclValue();
		}
		else
		{
			// Add the square of every errorValue in the errorVector
			for (int i = 0; i < errorVector.getEigenValue().rows(); i++)
			{
				specificError += pow(errorVector.getEigenValue()(i), 2.0);
			}

			// Divide the specific error by two
			specificError /= 2;
		}

		return specificError;
	}


	void AbstractTeachingLesson::calcSpecificError(viennacl::scalar<float>& specificError, viennacl::vector<float>& errorVector) const
	{
		viennacl::ocl::enqueue(calcSpecificErrorKernel->use()(
			viennacl::traits::opencl_handle(errorVector),
			cl_uint(viennacl::traits::start(errorVector)),
			cl_uint(viennacl::traits::stride(errorVector)),
			cl_uint(viennacl::traits::size(errorVector)),

			viennacl::traits::opencl_handle(specificError)
		));
	}
}
