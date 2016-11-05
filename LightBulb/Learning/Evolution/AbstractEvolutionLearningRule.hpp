#pragma once

#ifndef _ABSTRACTEVOLUTIONLEARNINGRULE_H_
#define _ABSTRACTEVOLUTIONLEARNINGRULE_H_

// Library Includes

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Random/ZigguratGenerator.hpp"

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
		template <class Archive>
		friend void serialize(Archive& archive, AbstractEvolutionLearningRule& evolutionLearning);
	private:
	protected:
		std::shared_ptr<ZigguratGenerator> zigguratGenerator;
		const AbstractEvolutionLearningRuleOptions& getOptions() const;
		virtual void setHelperToUsedObjects() {};
	public:
		AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions& options_);
		AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions* options_);
		std::vector<std::string> getDataSetLabels() const override;
		virtual const AbstractEvolutionWorld& getWorld() const;
		virtual AbstractEvolutionWorld& getWorld();
	};

}

#include "IO/AbstractEvolutionLearningRuleIO.hpp"


#endif


