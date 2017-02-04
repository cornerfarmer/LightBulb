// Includes
#include "LightBulb/IO/AbstractLearningRuleIO.hpp"
#include "LightBulb/IO/IOStorage.hpp"
#include "LightBulb/Learning/LearningState.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include "LightBulb/IO/TemplateDeclaration.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractLearningRule
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The AbstractLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractLearningRule& learningRule)
	{
		IOStorage<std::map<std::string, bool>>::push(&learningRule.options->disabledDataSets);
		archive(cereal::make_nvp("learningState", learningRule.learningState));
		archive(cereal::make_nvp("randomGenerator", learningRule.randomGenerator));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(AbstractLearningRule);
}