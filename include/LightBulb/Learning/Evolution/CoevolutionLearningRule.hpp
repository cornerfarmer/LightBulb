#pragma once

#ifndef _COEVOLUTIONLEARNINGRULE_H_
#define _COEVOLUTIONLEARNINGRULE_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractEvolutionLearningRule.hpp"

// Library Includes

namespace LightBulb
{
	/**
	* \brief All options for the coevolution learning rule.
	*/
	struct CoevolutionLearningRuleOptions : public AbstractEvolutionLearningRuleOptions
	{
		/**
		 * \brief The learning rule which contains the first population.
		 */
		AbstractEvolutionLearningRule* learningRule1;
		/**
		 * \brief The learning rule which contains the second/parasite population.
		 */
		AbstractEvolutionLearningRule* learningRule2;
		/**
		* \brief Creates the options and fills them with default options.
		*/
		CoevolutionLearningRuleOptions()
		{
			learningRule1 = nullptr;
			learningRule2 = nullptr;
		}
	};
	/**
	 * \brief Describes an (competitive) coevolution learning rule which contains two separate populations.
	 * \details One population (called parasite population) tries to make the other population loose. Having two separate populations makes it easier to learn and to hold learned stuff.
	 */
	class CoevolutionLearningRule : public AbstractEvolutionLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, CoevolutionLearningRule& learningRule);
		friend struct cereal::LoadAndConstruct<CoevolutionLearningRule>;
	protected:
		/**
		* \brief Returns our current options in form of a CoevolutionLearningRuleOptions object.
		* \return The CoevolutionLearningRuleOptions object.
		*/
		const CoevolutionLearningRuleOptions& getOptions() const;
		/**
		 * \brief True, if the exit condition of the first learning rule hase been reached.
		 */
		bool exitConditionReached;
		// Inherited:
		void doIteration() override;
		void initializeTry() override;
		bool hasLearningSucceeded() override;
		void initializeStartLearningAlgoritm() override;
		AbstractLearningResult* getLearningResult() override;
	public:
		/**
		* \brief Creates the coevolution learning rule.
		* \param options_ The options which configure the coevolution learning rule.
		*/
		CoevolutionLearningRule(CoevolutionLearningRuleOptions& options_);
		/**
		* \brief Creates the coevolution learning rule.
		* \param options_ The options which configure the coevolution learning rule.
		*/
		CoevolutionLearningRule(CoevolutionLearningRuleOptions* options_);
		/**
		* \brief Returns the name of the learning rule
		* \return The name
		*/
		static std::string getName();
		/**
		 * \brief Returns the learning rule which contains the first population.
		 * \return The learning rule which contains the first population.
		 */
		AbstractEvolutionLearningRule& getFirstLearningRule();
		/**
		 * \brief Returns the learning rule which contains the second/parasite population.
		 * \return The learning rule which contains the second/parasite population.
		 */
		AbstractEvolutionLearningRule& getSecondLearningRule();
		// Inherited:
		std::vector<std::string> getDataSetLabels() const override;
	};
}

#include "LightBulb/IO/CoevolutionLearningRuleIO.hpp"

#endif
