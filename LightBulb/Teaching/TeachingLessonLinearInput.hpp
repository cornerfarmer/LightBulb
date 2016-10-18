#pragma once

#ifndef _TEACHINGLESSONLINEARINPUT_H_
#define _TEACHINGLESSONLINEARINPUT_H_

// Library Includes
#include <vector>

// Includes
#include "Teaching/AbstractTeachingLesson.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a standard teaching lesson with linear teaching input.
	 */
	class TeachingLessonLinearInput : public AbstractTeachingLesson
	{
	private:
		/**
		 * \brief The values the neural network should return.
		 */
		std::unique_ptr<NeuralNetworkIO<double>> teachingInput;
		/**
		 * \brief  The values we will be fed into the neural network.
		 */
		std::vector<std::vector<double>> teachingPattern;
	protected:
		/**
		 * \brief Unfolds the teaching pattern.
		 * \return The unfolded teaching pattern.
		 */
		std::vector<std::vector<double>> unfoldTeachingPattern() const;
	public:
		/**
		 * \brief Creats a teaching lesson with linear input.
		 * \param teachingPattern_ The teaching pattern. (The input values of the network)
		 * \param teachingInput_ The teaching input. (The values the network should calculate)
		 */
		TeachingLessonLinearInput(std::vector<std::vector<double>> teachingPattern_, NeuralNetworkIO<double>* teachingInput_);
		// Inherited:
		AbstractTeachingLesson* unfold() const override;
		int getMaxTimeStep() const override;
		const NeuralNetworkIO<double>* getTeachingInput(const AbstractActivationFunction* activationFunction) const override;
		const std::vector<std::vector<double>>* getTeachingPattern() const override;
	};
}

#endif

