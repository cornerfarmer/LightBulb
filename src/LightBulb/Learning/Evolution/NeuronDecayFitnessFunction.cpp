// Includes
#include "LightBulb/Learning/Evolution/NeuronDecayFitnessFunction.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"

// Library includes

namespace LightBulb
{
	NeuronDecayFitnessFunction::NeuronDecayFitnessFunction(double fac_)
	{
		fac = fac_;
	}

	void NeuronDecayFitnessFunction::execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			entry->first -= fac * entry->second->getNeuralNetwork().getNetworkTopology().getNeuronCount();
		}
		sort(highscore.begin(), highscore.end(), std::greater<std::pair<double, AbstractIndividual*>>());
	}

	AbstractCloneable* NeuronDecayFitnessFunction::clone() const
	{
		return new NeuronDecayFitnessFunction(*this);
	}
}
