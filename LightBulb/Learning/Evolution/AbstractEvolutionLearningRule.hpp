#pragma once

#ifndef _ABSTRACTEVOLUTIONLEARNINGRULE_H_
#define _ABSTRACTEVOLUTIONLEARNINGRULE_H_

// Library Includes

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionWorld;

	struct AbstractEvolutionLearningRuleOptions : public AbstractLearningRuleOptions
	{
		AbstractEvolutionWorld* world;
		AbstractEvolutionLearningRuleOptions()
		{
			world = nullptr;
		}
	};

	// A LearningRule is used to improve a AbstractNeuralNetwork
	class AbstractEvolutionLearningRule : public AbstractLearningRule
	{
		friend class BipartiteEvolutionLearningRule;
	private:
	protected:
		const AbstractEvolutionLearningRuleOptions& getOptions();
		virtual void setHelperToUsedObjects() {};
	public:
		AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions& options_);
		AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions* options_);
		std::vector<std::string> getDataSetLabels() const override;
		virtual AbstractEvolutionWorld& getWorld() const;
	};

}

USE_PARENT_SINGLE_SERIALIZATION(LightBulb::AbstractEvolutionLearningRule, LightBulb::AbstractLearningRule, LightBulb);


#endif


