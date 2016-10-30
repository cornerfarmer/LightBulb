// Includes
#include "Learning/Evolution/NeuronDecayFitnessFunction.hpp"
#include "AbstractEvolutionObject.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

// Library includes

namespace LightBulb
{
	NeuronDecayFitnessFunction::NeuronDecayFitnessFunction(double fac_)
	{
		fac = fac_;
	}

	void NeuronDecayFitnessFunction::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			entry->first -= fac * entry->second->getNeuralNetwork().getNetworkTopology().getNeuronCount();
		}
		std::sort(highscore.begin(), highscore.end(), std::greater<std::pair<double, AbstractEvolutionObject*>>());
	}

	AbstractCloneable* NeuronDecayFitnessFunction::clone() const
	{
		return new NeuronDecayFitnessFunction(*this);
	}
}
