#pragma once

#ifndef _TEACHER_H_
#define _TEACHER_H_

// Includes
#include "AbstractTeachingLesson.hpp"
#include "AbstractTeacher.hpp"

// Library includes

namespace LightBulb
{
	/**
	* \brief Describes a teacher which provides all information the network should learn.
	* \details Contains multiple teaching and testing lessons which determine the values the network should calculate.
	*/
	class Teacher : public AbstractTeacher
	{
	private:
		/**
		 * \brief The weight decay factor to use.
		 */
		double weightDecayFac;
		/**
		 * \brief A list of teaching lessons which are used for total error calculation and learning stuff.
		 */
		std::vector<std::unique_ptr<AbstractTeachingLesson>> teachingLessons;
		/**
		 * \brief A list of teaching lessons which influent the total error, but they will not be part of any learning process.
		 */
		std::vector<std::unique_ptr<AbstractTeachingLesson>> testingLessons;
	public:
		/**
		 * \brief Creats the teacher.
		 * \param weightDecayFac_ The weight decay factor to use.
		 */
		Teacher(double weightDecayFac_ = 0);
		// Inherited:
		void addTeachingLesson(AbstractTeachingLesson* newTeachingLesson) override;
		void addTestingLesson(AbstractTeachingLesson* newTestingLesson) override;
		const std::vector<std::unique_ptr<AbstractTeachingLesson>>& getTeachingLessons() const override;
		const std::vector<std::unique_ptr<AbstractTeachingLesson>>& getTestingLessons() const override;
		double getTotalError(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder) const override;
		double getTeachingError(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder) const override;
		double getWeightDecayError(AbstractNeuralNetwork &neuralNetwork) const override;
		void clearLessons() override;
	};
}

#endif
