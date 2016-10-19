#pragma once

#ifndef _FUNCTIONSIMULATOR_H_
#define _FUNCTIONSIMULATOR_H_

// Library Includes
#include <vector>
#include <map>

// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class AbstractTile;

struct FunctionSimulatorOptions
{
	bool enableGraphics;
	FunctionSimulatorOptions()
	{
		enableGraphics = true;
	}
};

typedef double(*Function)(std::vector<float> pos);

class FunctionSimulator : public LightBulb::AbstractSimpleEvolutionWorld
{
protected:
	LightBulb::AbstractEvolutionObject* createNewObject() override;
	//std::unique_ptr<FunctionDrawer> drawer;
	std::unique_ptr<FunctionSimulatorOptions> options;
	Function function;
public:
	FunctionSimulator(FunctionSimulatorOptions &options_, Function function_);
	FunctionSimulator() = default;
	bool doSimulationStep() override;
	double getScore(LightBulb::AbstractEvolutionObject* object) override;
};

USE_EXISTING_PARENT_SERIALIZATION(FunctionSimulator, LightBulb::AbstractSimpleEvolutionWorld, LightBulb::AbstractEvolutionWorld)

#endif
