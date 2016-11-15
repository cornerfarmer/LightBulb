#pragma once

#ifndef _BIPARTITEEVOLUTIONLEARNINGRULE_H_
#define _BIPARTITEEVOLUTIONLEARNINGRULE_H_

// Includes
#include "Learning/Evolution/AbstractEvolutionLearningRule.hpp"

// Library Includes

namespace LightBulb
{
	/**
	* \brief All options for the bipartite evolution learning rule.
	*/
	struct BipartiteEvolutionLearningRuleOptions : public AbstractEvolutionLearningRuleOptions
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
		BipartiteEvolutionLearningRuleOptions()
		{
			learningRule1 = nullptr;
			learningRule2 = nullptr;
		}
	};
	/**
	 * \brief Describes an evolution learning rule which contains two separate populations.
	 * \details One population (called parasite population) tries to make the other population loose. Having two separate populations makes it easier to learn and to hold learned stuff.
	 */
	class BipartiteEvolutionLearningRule : public AbstractEvolutionLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, BipartiteEvolutionLearningRule& learningRule);
		friend struct cereal::LoadAndConstruct<BipartiteEvolutionLearningRule>;
	protected:
		/**
		* \brief Returns our current options in form of a BipartiteEvolutionLearningRuleOptions object.
		* \return The BipartiteEvolutionLearningRuleOptions object.
		*/
		const BipartiteEvolutionLearningRuleOptions& getOptions() const;
		/**
		 * \brief True, if the exit condition of the first learning rule hase been reached.
		 */
		bool exitConditionReached;
		// Inherited:
		bool doIteration() override;
		void initializeTry() override;
		bool hasLearningSucceeded() override;
		void initializeStartLearningAlgoritm() override;
		AbstractLearningResult* getLearningResult() override;
	public:
		/**
		* \brief Creates the bipartite evolution learning rule.
		* \param options_ The options which configure the bipartite evolution learning rule.
		*/
		BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions& options_);
		/**
		* \brief Creates the bipartite evolution learning rule.
		* \param options_ The options which configure the bipartite evolution learning rule.
		*/
		BipartiteEvolutionLearningRule(BipartiteEvolutionLearningRuleOptions* options_);
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

#include "IO/BipartiteEvolutionLearningRuleIO.hpp"

#endif
