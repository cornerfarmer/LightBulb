#pragma once

#ifndef _PONGREINFORCEMENTENVIRONMENT_H_
#define _PONGREINFORCEMENTENVIRONMENT_H_

// Library Includes

// Include
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "Examples/PongEvolution/AbstractPongEnvironment.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"

// Forward declarations

class PongReinforcementEnvironment : public LightBulb::AbstractReinforcementEnvironment, public AbstractPongEnvironment
{
	template <class Archive>
	friend void serialize(Archive& archive, PongReinforcementEnvironment& environment);
	friend struct cereal::LoadAndConstruct<PongReinforcementEnvironment>;
private:
	std::unique_ptr<LightBulb::Kernel> getNnInputKernel;
	std::unique_ptr<LightBulb::Kernel> getNnInputOnlyKernel;
	std::unique_ptr<LightBulb::Kernel> interpretNnOutputKernel;
	std::unique_ptr<LightBulb::Kernel> isTerminalStateKernel;
	LightBulb::Scalar<int> time;
	LightBulb::Scalar<>* rewardTmp;
	bool inSimulationPhase;
	void initializeKernels();
	void reset();
public:
	PongReinforcementEnvironment();
	void doSimulationStep(LightBulb::Scalar<>& reward) override;
	void executeCompareAI();
	void initializeForLearning() override;
	std::vector<std::string> getDataSetLabels() const override;
	void isTerminalState(LightBulb::Scalar<char>& isTerminalState) const;
	void getNNInput(LightBulb::Vector<>& input) const;
	void interpretNNOutput(LightBulb::Vector<char>& output);
	void setRandomGenerator(LightBulb::AbstractRandomGenerator& randomGenerator_) override;
};


#include "IO/PongReinforcementEnvironmentIO.hpp"

#endif
