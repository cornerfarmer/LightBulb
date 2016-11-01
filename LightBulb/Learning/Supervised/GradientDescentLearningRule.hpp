#pragma once

#ifndef _GRADIENTDESCENTLEARNINGRULE_H_
#define _GRADIENTDESCENTLEARNINGRULE_H_

// Library Includes
#include <vector>
#include <map>
#include <EigenSrc/Dense>

// Includes
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"
#include <cereal/access.hpp>
#include "GradientCalculation/AbstractGradientCalculation.hpp"
#include "GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"

namespace LightBulb
{
	/**
	* \brief All options for the gradient descent learning rule.
	*/
	struct GradientDescentLearningRuleOptions : public AbstractSupervisedLearningRuleOptions
	{
		/**
		 * \brief The algorithm which calculates the gradient.
		 */
		AbstractGradientCalculation* gradientCalculation;
		/**
		 * \brief The algorithm which does the gradient descent.
		 * \details It calculates the delta weights from the given gradient.
		 */
		AbstractGradientDescentAlgorithm* gradientDescentAlgorithm;
		/**
		 * \brief Creates the options and fills them with default options.
		 */
		GradientDescentLearningRuleOptions()
		{
			offlineLearning = false;
			gradientCalculation = nullptr;
			gradientDescentAlgorithm = nullptr;
		}
		~GradientDescentLearningRuleOptions();
		GradientDescentLearningRuleOptions(const GradientDescentLearningRuleOptions& other);
		GradientDescentLearningRuleOptions(GradientDescentLearningRuleOptions&& other) noexcept;
		GradientDescentLearningRuleOptions& operator=(GradientDescentLearningRuleOptions other);
		friend void swap(GradientDescentLearningRuleOptions& lhs, GradientDescentLearningRuleOptions& rhs) noexcept;
	};

	/**
	 * \brief A simple gradient descent learning rule.
	 * \details The learning rule first calculates the gradient and then executes a descent step.
	 */
	class GradientDescentLearningRule : public AbstractSupervisedLearningRule
	{
		friend class CascadeCorrelationLearningRule;
		template <class Archive>
		friend void serialize(Archive& archive, GradientDescentLearningRule& learningRule);
		friend struct cereal::LoadAndConstruct<GradientDescentLearningRule>;
	private:
		/**
		 * \brief The algorithm which calculates the gradient.
		 */
		std::unique_ptr<AbstractGradientCalculation> gradientCalculation;
		/**
		 * \brief The algorithm which does the gradient descent.
		 */
		std::unique_ptr<AbstractGradientDescentAlgorithm> gradientDescentAlgorithm;
		/**
		 * \brief Initializes the learning rule.
		 */
		void initialize(GradientDescentLearningRuleOptions* options);
	protected:
		/**
		 * \brief Returns our current options in form of a GradientDescentLearningRuleOptions object.
		 * \return The GradientDescentLearningRuleOptions object.
		 */
		const GradientDescentLearningRuleOptions* getOptions() const;
		// Inherited:
		/**
		 * \brief Executes the gradient decent algorithm and adds its return to the weights.
		 * \param layerIndex The current layer
		 */
		void adjustWeights(int layerIndex) override;
		void clearGradient() override;
		std::string printDebugOutput() override;
		bool learningHasStopped() override;
		/**
		 * \brief Calculates the gradient.
		 * \param lesson The current teaching lesson object.
		 * \param lessonIndex The current teaching lesson index.
		 * \param errormap The errormap which represents how well the neural network has done on the current teaching lesson.
		 */
		void calculateDeltaWeight(const AbstractTeachingLesson& lesson, int lessonIndex, const ErrorMap_t& errormap) override;
		void initializeTry() override;
	public:
		/**
		* \brief Creates the gradient descent learning rule.
		* \param options_ The options which configure the gradient descent learning rule.
		 */
		GradientDescentLearningRule(GradientDescentLearningRuleOptions& options_);
		/**
		* \brief Creates the gradient descent learning rule.
		* \param options_ The options which configure the gradient descent learning rule.
		*/
		GradientDescentLearningRule(GradientDescentLearningRuleOptions* options_);
		/**
		* \brief Creates the gradient descent learning rule with default options.
		*/
		GradientDescentLearningRule();
		/**
		 * \brief Returns the name of the learning rule
		 * \return The name
		 */
		static std::string getName();
	};
}

#include "IO/GradientDescentLearningRuleIO.hpp"

#endif

