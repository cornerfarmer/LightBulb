#pragma once

#ifndef _TEACHINGLESSONBOOLEANINPUT_H_
#define _TEACHINGLESSONBOOLEANINPUT_H_

// Library Includes
#include <vector>

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
		std::unique_ptr<TeachingInput<char>> teachingInput;
		/**
		 * \brief The values the neural network should give back as doubles.
		 * \details These are calculated dynamically.
		 */
		std::unique_ptr<TeachingInput<>> teachingInputLinear;
		/**
		 * \brief The values we will put into the neural network
		 */
		std::unique_ptr<Vector<>> teachingPattern;
	public:
		/**
		 * \brief Creates a teaching lesson with boolean input
		 * \param teachingPattern_ The teaching pattern. (The input values of the network)
		 * \param teachingInput_ The teaching input. (The values the network should calculate)
		 */
		TeachingLessonBooleanInput(Vector<>* teachingPattern_, TeachingInput<char>* teachingInput_);
		// Inherited:
		const TeachingInput<>& getTeachingInput(const AbstractActivationFunction& activationFunction) const override;
		TeachingInput<char>& getBooleanTeachingInput() const;
		const Vector<>& getTeachingPattern() const override;
	};
}

#endif

