#pragma once

#ifndef _ABSTRACTREINFORCEMENTLEARNINGRULEINGRULE_H_
#define _ABSTRACTREINFORCEMENTLEARNINGRULEINGRULE_H_

// Includes
#include "Learning/AbstractLearningRule.hpp"

// Library Includes

namespace LightBulb
{
	// Forward declarations
	class AbstractReinforcementWorld;
	/**
	* \brief All general options which are the same for all reinforcement learning rules.
	*/
	struct AbstractReinforcementLearningRuleOptions : public AbstractLearningRuleOptions
	{
		/**
		* \brief The world which is used by this learning rule.
		*/
		AbstractReinforcementWorld* world;
		/**
		* \brief Creates the options and fills them with default options.
		*/
		AbstractReinforcementLearningRuleOptions()
		{
			world = nullptr;
			maxIterationsPerTry = 10000000000;
		}
	};

	#define DATA_SET_REWARD "Reward"

	/**
	 * \brief Describes a reinforcement learning rule.
	 * \details This kind of algorithm only needs a reward which describes how well the actor has done to learn.
	 */
	class AbstractReinforcementLearningRule : public AbstractLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractReinforcementLearningRule& learningRule);
	private:
	protected:
		/**
		* \brief Returns our current options in form of a AbstractReinforcementLearningRuleOptions object.
		* \return The AbstractReinforcementLearningRuleOptions.
		*/
		virtual const AbstractReinforcementLearningRuleOptions& getOptions() const;
		/**
		 * \brief Should be called after the random generator has been changed.
		 */
		void randomGeneratorHasChanged();
		// Inherited:
		bool hasLearningSucceeded() override;
	public:
		/**
		 * \brief Creates the reinforcement learning rule.
		 * \param options_ The options which configure the supervised learning rule.
		 */
		AbstractReinforcementLearningRule(AbstractReinforcementLearningRuleOptions* options_);
		AbstractReinforcementLearningRule() = default;
		// Inherited:
		std::vector<std::string> getDataSetLabels() const override;
	};
}

#include "IO/AbstractReinforcementLearningRuleIO.hpp"

#endif
