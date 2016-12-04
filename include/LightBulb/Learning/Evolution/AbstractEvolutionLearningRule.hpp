#pragma once

#ifndef _ABSTRACTEVOLUTIONLEARNINGRULE_H_
#define _ABSTRACTEVOLUTIONLEARNINGRULE_H_

// Library Includes

// Includes
#include "LightBulb/Learning/AbstractLearningRule.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/Random/ZigguratGenerator.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionEnvironment;

	/**
	* \brief All general options which are the same for all evolution learning rules.
	*/
	struct AbstractEvolutionLearningRuleOptions : public AbstractLearningRuleOptions
	{
		/**
		 * \brief The environment which is used by this learning rule.
		 */
		AbstractEvolutionEnvironment* environment;
		/**
		* \brief Creates the options and fills them with default options.
		*/
		AbstractEvolutionLearningRuleOptions()
		{
			environment = nullptr;
		}
	};
	/**
	 * \brief Describes a learning rule which uses evolution to train neural networks.
	 */
	class AbstractEvolutionLearningRule : public AbstractLearningRule
	{
		friend class CoevolutionLearningRule;
		template <class Archive>
		friend void serialize(Archive& archive, AbstractEvolutionLearningRule& evolutionLearning);
	private:
	protected:
		/**
		 * \brief The ziggurat generator which is used to generate random numbers from a normal distribution.
		 */
		std::shared_ptr<ZigguratGenerator> zigguratGenerator;
		/**
		* \brief Returns our current options in form of a AbstractEvolutionLearningRuleOptions object.
		* \return The AbstractEvolutionLearningRuleOptions.
		*/
		const AbstractEvolutionLearningRuleOptions& getOptions() const;
		/**
		 * \brief Resets helper objects like logger to all commands.
		 */
		virtual void setHelperToUsedObjects() {};
	public:
		/**
		* \brief Creates the evolution learning rule.
		* \param options_ The options which configure the evolution learning rule.
		*/
		AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions& options_);
		/**
		* \brief Creates the evolution learning rule.
		* \param options_ The options which configure the evolution learning rule.
		*/
		AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions* options_);
		/**
		 * \brief Returns the corresponding environment.
		 * \return The environment which is used by this learning rule.
		 */
		virtual const AbstractEvolutionEnvironment& getEnvironment() const;
		/**
		* \brief Returns the corresponding environment.
		* \return The environment which is used by this learning rule.
		*/
		virtual AbstractEvolutionEnvironment& getEnvironment();
		// Inherited:
		std::vector<std::string> getDataSetLabels() const override;
	};

}

#include "LightBulb/IO/AbstractEvolutionLearningRuleIO.hpp"


#endif


