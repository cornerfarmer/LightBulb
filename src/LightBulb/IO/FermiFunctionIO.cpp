// Includes
#include "LightBulb/IO/FermiFunctionIO.hpp"
#include "LightBulb/IO/TemplateDeclaration.hpp"
// Libary includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a FermiFunction.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param fermiFunction The FermiFunction to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, FermiFunction& fermiFunction)
	{
		archive(cereal::make_nvp("temperatureParameter", fermiFunction.temperatureParameter));
		archive(cereal::base_class<AbstractActivationFunction>(&fermiFunction));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(FermiFunction);
}

namespace cereal
{
	/**
	* \brief Constructs a FermiFunction.
	* \tparam Archive The archive type.
	* \param ar The archive which should be used.
	* \param construct The FermiFunction construct object.
	*/
	template <class Archive>
	void LoadAndConstruct<LightBulb::FermiFunction>::load_and_construct(Archive & ar, construct<LightBulb::FermiFunction>& construct)
	{
		double temperatureParameter;
		ar(make_nvp("temperatureParameter", temperatureParameter));
		construct(temperatureParameter);
		ar(cereal::base_class<LightBulb::AbstractActivationFunction>(construct.ptr()));
	}

	DECLARE_LOAD_AND_CONSTRUCT_TEMPLATE(LightBulb::FermiFunction);
}


#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::FermiFunction);

CEREAL_REGISTER_DYNAMIC_INIT(FermiFunction)