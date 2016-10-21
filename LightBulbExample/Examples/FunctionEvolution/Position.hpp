#pragma once

#ifndef _POSITION_H_
#define _POSITION_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"

// Forward declarations
class FunctionSimulator;

class Position : public LightBulb::AbstractSimpleEvolutionObject
{
	template <class Archive>
	friend void save(Archive& archive, Position const& object);
	template <class Archive>
	friend void load(Archive& archive, Position& object);
protected:
	FunctionSimulator* functionSimulator;
	std::vector<float> position;
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<double>& output) override;
public:	
	Position(FunctionSimulator& functionSimulator_);
	Position() = default;
	~Position();
	std::vector<float> getPosition();
};

#include "IO/PositionIO.hpp"

#endif
