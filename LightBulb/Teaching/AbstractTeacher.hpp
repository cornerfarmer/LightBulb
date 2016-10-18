#pragma once

#ifndef _ABSTRACTTEACHER_H_
#define _ABSTRACTTEACHER_H_

// Includes

// Library includes
#include <vector>
#include <memory>

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	class AbstractActivationOrder;
	class AbstractTeachingLesson;

	/**
	 * \brief Describes a teacher which provides all information the network should learn.
	 * \details Contains multiple teaching and testing lessons which determine the values the network should calculate.
	 */
	class AbstractTeacher
	{
	private:
	public:
		virtual ~AbstractTeacher() {};
		/**
		 * \brief Adds a new teaching lesson to the teacher.
		 * \param newTeachingLesson The new teaching lesson.
		 */
		virtual void addTeachingLesson(AbstractTeachingLesson* newTeachingLesson) = 0;
		/**
		 * \brief Adds a new testing lesson to the teacher.
		 * \param newTestingLesson  The new testing lesson.
		 */
		virtual void addTestingLesson(AbstractTeachingLesson* newTestingLesson) = 0;
		/**
		 * \brief Returns all teaching lessons.
		 * \return All teaching lessons.
		 */
		const virtual std::vector<std::unique_ptr<AbstractTeachingLesson>>* getTeachingLessons() const = 0;
		/**
		 * \brief Returns all testing lessons.
		 * \return All testing lessons.
		 */
		const virtual std::vector<std::unique_ptr<AbstractTeachingLesson>>* getTestingLessons() const = 0;
		/**
		 * \brief Calculates the total error from all teaching and testing lessons plus the weight decay error.
		 * \details Calculates getTeachingError() + getWeightDecayError().
		 * \param neuralNetwork The neural network to evaluate.
		 * \param activationOrder The activation order to use.
		 * \return The total error.
		 */
		virtual double getTotalError(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder) const = 0;
		/**
		 * \brief Returns the teaching error. Uses the squared error.
		 * \details Calculates: \f$ E=0.5*\sum{(t_i-y_i)^2} \f$
		 * \param neuralNetwork The neural network to evaluate.
		 * \param activationOrder The activation order to use.
		 * \return The teaching error.
		 */
		virtual double getTeachingError(AbstractNeuralNetwork &neuralNetwork, const AbstractActivationOrder &activationOrder) const = 0;
		/**
		 * \brief Calculates the weight decay error.
		 * \details Calculates: \f$ E=\sum{\omega_{i,j}^2} \f$
		 * \param neuralNetwork The neural network to evaluate.
		 * \return The weight decay error.
		 */
		virtual double getWeightDecayError(AbstractNeuralNetwork &neuralNetwork) const = 0;
		/**
		 * \brief Returns a unfolded version of this teacher.
		 * \return The unfolded teacher.
		 * TODO: Remove?
		 */
		virtual AbstractTeacher* unfold() const = 0;
		/**
		 * \brief Returns the biggest used timestep of all teaching lessons.
		 * \return The maximum timestep.
		 */
		virtual int getMaxTimeStep() const = 0;
		/**
		 * \brief Removes all teaching and testing lessons.
		 */
		virtual void clearLessons() = 0;
	};
}

#endif
