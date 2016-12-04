#pragma once

#ifndef _ABSTRACTLEARNINGRULETRAININGPLAN_H_
#define _ABSTRACTLEARNINGRULETRAININGPLAN_H_


// Includes
#include "LightBulbApp/TrainingPlans/AbstractTrainingPlan.hpp"
#include "LightBulb/Learning/AbstractLearningResult.hpp"
#include "LightBulb/Learning/AbstractLearningRule.hpp"

// Library includes

namespace LightBulb
{
	/**
	 * \brief Describes a learning rule which uses a learning rule.
	 */
	class AbstractLearningRuleTrainingPlan : public AbstractTrainingPlan
	{
		template <class Archive>
		friend void load(Archive& archive, AbstractLearningRuleTrainingPlan& trainingPlan);
		template <class Archive>
		friend void save(Archive& archive, AbstractLearningRuleTrainingPlan const& trainingPlan);
	private:
		/**
		 * \brief True, if a pause has been requested.
		 */
		bool pauseRequested;
		/**
		 * \brief The result of the learning rule.
		 */
		std::unique_ptr<AbstractLearningResult> learningResult;
		/**
		 * \brief The learning rule.
		 */
		std::unique_ptr<AbstractLearningRule> learningRule;
	protected:
		/**
		 * \brief Creates the learning rule.
		 * \return The new learning rule.
		 */
		virtual AbstractLearningRule* createLearningRate() = 0;
		/**
		 * \brief Fills all learning rule options which are the same for all learning rule training plans.
		 * \param options The options to fill.
		 */
		virtual void fillDefaultLearningRuleOptions(AbstractLearningRuleOptions& options) const;
		// Inherited:
		void run(bool initial) override;
		void tryToPause() override;
	public:
		/**
		 * \brief Returns the learning result.
		 * \return The learning result.
		 */
		const AbstractLearningResult& getLearningResult() const;
		/**
		 * \brief Returns the learning rule.
		 * \return The learning rule.
		 */
		AbstractLearningRule& getLearningRule();
		// Inherited:
		std::vector<std::string> getDataSetLabels() const override;
		LearningState& getLearningState() override;
		bool hasLearningState() override;
		int getSeed() const override;
	};
}

#include "LightBulbApp/IO/AbstractLearningRuleTrainingPlanIO.hpp"

#endif
