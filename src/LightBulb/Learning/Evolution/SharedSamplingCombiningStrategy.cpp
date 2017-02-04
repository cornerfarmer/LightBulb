// Includes
#include "LightBulb/Learning/Evolution/SharedSamplingCombiningStrategy.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp"
//Library includes

namespace LightBulb
{
	void SharedSamplingCombiningStrategy::combine(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals)
	{
		if (!otherCombiningStrategy)
			throw std::invalid_argument("SharedSamplingCombiningStrategy only works with two environments.");

		std::vector<AbstractIndividual*> sample;
		std::map<AbstractIndividual*, std::map<int, int>> beat;
		std::map<AbstractIndividual*, double> sampleFitness;
		auto prevResults = otherCombiningStrategy->getPrevResults();
		while (sample.size() < amountOfCompetitionsPerIndividual)
		{
			AbstractIndividual* bestIndividual = nullptr;
			for (auto secondPlayer = secondIndividuals.begin(); secondPlayer != secondIndividuals.end(); secondPlayer++)
			{
				if (sampleFitness[*secondPlayer] != -1)
				{
					sampleFitness[*secondPlayer] = 0;
					for (auto resultsPerSecondPlayer = prevResults[*secondPlayer].begin(); resultsPerSecondPlayer != prevResults[*secondPlayer].end(); resultsPerSecondPlayer++)
					{
						for (auto result = resultsPerSecondPlayer->second.begin(); result != resultsPerSecondPlayer->second.end(); result++)
						{
							if (result->second)
								sampleFitness[*secondPlayer] += 1.0 / (1 + beat[resultsPerSecondPlayer->first][result->first]);
						}
					}
					if (bestIndividual == nullptr || sampleFitness[bestIndividual] < sampleFitness[*secondPlayer])
						bestIndividual = *secondPlayer;
				}
			}
			if (!bestIndividual)
				break;

			sample.push_back(bestIndividual);
			sampleFitness[bestIndividual] = -1;
			for (auto resultsPerSecondPlayer = prevResults[bestIndividual].begin(); resultsPerSecondPlayer != prevResults[bestIndividual].end(); resultsPerSecondPlayer++)
			{
				for (auto result = resultsPerSecondPlayer->second.begin(); result != resultsPerSecondPlayer->second.end(); result++)
				{
					if (result->second)
						beat[resultsPerSecondPlayer->first][result->first]++;
				}
			}
		}

		for (auto firstPlayer = firstIndividuals.begin(); firstPlayer != firstIndividuals.end(); firstPlayer++)
		{
			for (auto secondPlayer = sample.begin(); secondPlayer != sample.end(); secondPlayer++)
			{
				if (*firstPlayer != *secondPlayer)
				{
					for (int r = 0; r < simulationEnvironment.getRoundCount(); r++)
					{
						int result = simulationEnvironment.compareIndividuals(**firstPlayer, **secondPlayer, r);
						if (result != 0)
							setResult(**firstPlayer, **secondPlayer, r, result > 0);
					}
				}
			}
		}
	}

	void SharedSamplingCombiningStrategy::setSecondEnvironment(AbstractCoevolutionEnvironment& newSecondEnvironment)
	{
		AbstractCombiningStrategy::setSecondEnvironment(newSecondEnvironment);
		otherCombiningStrategy = &secondEnvironment->getCombiningStrategy();
	}

	SharedSamplingCombiningStrategy::SharedSamplingCombiningStrategy(int amountOfCompetitionsPerIndividual_, AbstractCoevolutionEnvironment* secondEnvironment_)
		:AbstractCombiningStrategy(secondEnvironment_)
	{
		if (secondEnvironment)
			otherCombiningStrategy = &secondEnvironment->getCombiningStrategy();
		amountOfCompetitionsPerIndividual = amountOfCompetitionsPerIndividual_;
	}


	int SharedSamplingCombiningStrategy::getTotalMatches(const AbstractCoevolutionEnvironment& simulationEnvironment) const
	{
		return amountOfCompetitionsPerIndividual * simulationEnvironment.getPopulationSize() * simulationEnvironment.getRoundCount();
	}

}