#pragma once

#ifndef _CONSTANTRECOMBINATIONCOMMAND_H_
#define _CONSTANTRECOMBINATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "Function/RandomFunction/RankBasedRandomFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	class ConstantRecombinationCommand : public AbstractRecombinationCommand
	{
	private:
		// Holds amount of objects which should be combined
		int objectCount;
		// Alternative: Holds the percentage of objects which should be combined
		double recombinationPercentage;
	public:
		void setRecombinationPercentage(double newRecombinationPercentage);
		void setRecombinationCount(int newObjectCount);
		ConstantRecombinationCommand() = default;
		ConstantRecombinationCommand(const ConstantRecombinationCommand& other) = default;
		// Creates a command which combines a static amount of objects
		ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, int objectCount_);
		// Creates a command which combines a percentage of objects
		ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, double recombinationPercentage_);
		ConstantRecombinationCommand(ConstantRecombinationCommand&& other) noexcept;
		ConstantRecombinationCommand& operator=(ConstantRecombinationCommand other);

		friend void swap(ConstantRecombinationCommand& lhs, ConstantRecombinationCommand& rhs) noexcept;

		void select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter) override;

		AbstractCloneable* clone() const override;
	};
}

#endif
