// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/EvolutionLearningRuleIO.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an EvolutionLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The EvolutionLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, EvolutionLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractEvolutionLearningRule>(&learningRule));
		archive(cereal::make_nvp("zigguratGenerator", learningRule.zigguratGenerator));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(EvolutionLearningRule);
}

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::EvolutionLearningRule>::construct(Archive& ar, LightBulb::EvolutionLearningRule& learningRule)
	{
		ar(base_class<LightBulb::AbstractEvolutionLearningRule>(&learningRule));
		ar(cereal::make_nvp("zigguratGenerator", learningRule.zigguratGenerator));
		learningRule.setHelperToUsedObjects();
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::EvolutionLearningRule);

CEREAL_REGISTER_DYNAMIC_INIT(EvolutionLearningRule)