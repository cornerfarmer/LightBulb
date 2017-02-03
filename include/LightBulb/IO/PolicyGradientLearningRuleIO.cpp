// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/PolicyGradientLearningRuleIO.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a PolicyGradientLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The PolicyGradientLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, PolicyGradientLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractReinforcementLearningRule>(&learningRule));
		archive(cereal::make_nvp("valueFunctionNetwork", learningRule.valueFunctionNetwork));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(PolicyGradientLearningRule);
}


namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::PolicyGradientLearningRule>::construct(Archive& ar, LightBulb::PolicyGradientLearningRule& learningRule)
	{
		using namespace LightBulb;
		ar(base_class<AbstractReinforcementLearningRule>(&learningRule));
		ar(cereal::make_nvp("valueFunctionNetwork", learningRule.valueFunctionNetwork));
	}
}


#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::PolicyGradientLearningRule);
