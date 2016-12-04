#pragma once

#ifndef _TEACHINGLESSONBOOLEANINPUT_H_
#define _TEACHINGLESSONBOOLEANINPUT_H_

// Library Includes
#include <vector>
#include <list>

// Includes
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"

namespace LightBulb
{
	/**
	 * \brief Describes a teaching lesson which has boolean teaching input.
	 * \details The real teaching input is calculated depending on the activation function of the neural network in the output layer.
	 */
	class TeachingLessonBooleanInput : public AbstractTeachingLesson
	{
	private:
		/**
		 * \brief The values the neural network should give back as booleans.
		 */
		std::unique_ptr<TeachingInput<bool>> teachingInput;
		/**
		 * \brief The values the neural network should give back as doubles.
		 * \details These are calculated dynamically.
		 */
		std::unique_ptr<TeachingInput<double>> teachingInputLinear;
		/**
		 * \brief The values we will put into the neural network
		 */
		std::vector<double> teachingPattern;
	public:
		/**
		 * \brief Creates a teaching lesson with boolean input
		 * \param teachingPattern_ The teaching pattern. (The input values of the network)
		 * \param teachingInput_ The teaching input. (The values the network should calculate)
		 */
		TeachingLessonBooleanInput(std::vector<double> teachingPattern_, TeachingInput<bool>* teachingInput_);
		// Inherited:
		const TeachingInput<double>& getTeachingInput(const AbstractActivationFunction& activationFunction) const override;
		TeachingInput<bool>& getBooleanTeachingInput() const;
		const std::vector<double>& getTeachingPattern() const override;
	};
}

#endif

