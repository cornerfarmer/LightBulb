#pragma once

#ifndef _TEACHINGLESSONLINEARINPUT_H_
#define _TEACHINGLESSONLINEARINPUT_H_

// Library Includes
#include <vector>

// Includes
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"

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
		std::shared_ptr<TeachingInput<>> teachingInput;
		/**
		 * \brief  The values we will be fed into the neural network.
		 */
		std::shared_ptr<Vector<>> teachingPattern;
	public:
		/**
		 * \brief Creats a teaching lesson with linear input.
		 * \param teachingPattern_ The teaching pattern. (The input values of the network)
		 * \param teachingInput_ The teaching input. (The values the network should calculate)
		 */
		TeachingLessonLinearInput(Vector<>* teachingPattern_, TeachingInput<>* teachingInput_);
		/**
		* \brief Creats a teaching lesson with linear input.
		* \param teachingPattern_ The teaching pattern. (The input values of the network)
		* \param teachingInput_ The teaching input. (The values the network should calculate)
		*/
		TeachingLessonLinearInput(const std::shared_ptr<Vector<>>& teachingPattern_, const std::shared_ptr<TeachingInput<>>& teachingInput_);
		// Inherited:
		const TeachingInput<>& getTeachingInput(const AbstractActivationFunction& activationFunction) const override;
		const Vector<>& getTeachingPattern() const override;
	};
}

#endif

