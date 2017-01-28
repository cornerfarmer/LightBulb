#pragma once

#ifndef _NETWORKSIMULATOR_H_
#define _NETWORKSIMULATOR_H_

// Library Includes
#include <vector>
#include <map>

// Include
#include "LightBulb/Learning/Evolution/AbstractSimpleEvolutionEnvironment.hpp"

// Forward declarations

class NetworkSimulator : public LightBulb::AbstractSimpleEvolutionEnvironment
{
	template <class Archive>
	friend void save(Archive& archive, NetworkSimulator const& environment);
	template <class Archive>
	friend void load(Archive& archive, NetworkSimulator& environment);
	friend struct cereal::LoadAndConstruct<NetworkSimulator>;
protected:
	std::vector<std::vector<float>> consumers;
	LightBulb::AbstractIndividual* createNewIndividual() override;
	//sf::RenderWindow window;
	//std::unique_ptr<NetworkDrawer> drawer;
	double distanceBetweenPositions(const std::vector<float>& pos1, const std::vector<float>& pos2) const;
public:
	NetworkSimulator(std::vector<std::vector<float>> consumers_);
	NetworkSimulator() = default;
	void doSimulationStep() override;
	void getFitness(const LightBulb::AbstractIndividual& individual, LightBulb::Scalar<>& fitness) const override;
	std::vector<std::vector<float>>& getConsumers();
};

#include "IO/NetworkSimulatorIO.hpp"


#endif
