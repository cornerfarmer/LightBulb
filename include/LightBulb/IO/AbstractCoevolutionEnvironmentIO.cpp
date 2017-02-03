// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/AbstractCoevolutionEnvironmentIO.hpp"
#include "LightBulb/Learning/Evolution/AbstractHallOfFameAlgorithm.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	 * \brief Saves an AbstractCoevolutionEnvironment
	 * \tparam Archive The archive type.
	 * \param archive The archive which should be used.
	 * \param environment The AbstractCoevolutionEnvironment to save.
	 */
	template <class Archive>
	void save(Archive& archive, AbstractCoevolutionEnvironment const& environment)
	{
		archive(cereal::base_class<AbstractSimpleEvolutionEnvironment>(&environment));
		archive(cereal::make_nvp("hallOfFameToAddAlgorithm", environment.hallOfFameToAddAlgorithm));
		archive(cereal::make_nvp("hallOfFameToChallengeAlgorithm", environment.hallOfFameToChallengeAlgorithm));

		std::vector<double> fitnessValues(environment.individuals.size());
		for (int i = 0; i < environment.individuals.size(); i++)
		{
			if (environment.fitnessValues->count(environment.individuals[i]))
				fitnessValues[i] = environment.fitnessValues->at(environment.individuals[i]);
		}
		archive(cereal::make_nvp("fitnessValues", fitnessValues));

		archive(cereal::make_nvp("comparisons", environment.comparisons));
	}


	/**
	* \brief Loads an AbstractCoevolutionEnvironment
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param environment The AbstractCoevolutionEnvironment to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractCoevolutionEnvironment& environment)
	{
		archive(cereal::base_class<AbstractSimpleEvolutionEnvironment>(&environment));

		std::shared_ptr<AbstractHallOfFameAlgorithm> tmp(environment.hallOfFameToAddAlgorithm);

		IOStorage<AbstractHallOfFameAlgorithm>::push(environment.hallOfFameToAddAlgorithm.get());
		archive(cereal::make_nvp("hallOfFameToAddAlgorithm", environment.hallOfFameToAddAlgorithm));
		environment.hallOfFameToAddAlgorithm = tmp;

		tmp = environment.hallOfFameToChallengeAlgorithm;

		IOStorage<AbstractHallOfFameAlgorithm>::push(environment.hallOfFameToChallengeAlgorithm.get());
		archive(cereal::make_nvp("hallOfFameToChallengeAlgorithm", environment.hallOfFameToChallengeAlgorithm));
		environment.hallOfFameToChallengeAlgorithm = tmp;
		IOStorage<AbstractHallOfFameAlgorithm>::clear();

		tmp = nullptr;

		std::vector<double> fitnessValues;
		archive(cereal::make_nvp("fitnessValues", fitnessValues));
		environment.fitnessValues.reset(new std::map<const AbstractIndividual*, double>());
		for (int i = 0; i < environment.individuals.size(); i++)
			(*environment.fitnessValues)[environment.individuals[i]] = fitnessValues[i];

		archive(cereal::make_nvp("comparisons", environment.comparisons));
	}

	DECLARE_SERIALIZATION_TEMPLATE(AbstractCoevolutionEnvironment);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractCoevolutionEnvironment);

CEREAL_REGISTER_DYNAMIC_INIT(AbstractCoevolutionEnvironment)

