#pragma once

#ifndef _CONSTANTREUSECOMMAND_H_
#define _CONSTANTREUSECOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractReuseCommand.hpp"

namespace LightBulb
{
	// Forward declarations

	// A class to directly reuse the best N evolution objects
	class ConstantReuseCommand : public AbstractReuseCommand
	{
	private:
		// Holds amount of objects which should be reused
		int objectCount;
		// Alternative: Holds the percentage of objects which should be reused
		double reusePercentage;
	public:
		virtual ~ConstantReuseCommand() {};
		// Creates a command which reuses a static amount of objects
		ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, int objectCount_);
		// Creates a command which reuses a percentage of objects
		ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, double reusePercentage_);

		ConstantReuseCommand& operator=(ConstantReuseCommand other);
		friend void swap(ConstantReuseCommand& lhs, ConstantReuseCommand& rhs) noexcept;

		void select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter) override;
		void setReusePercentage(double newReusePercentage);
		void setReuseCount(double newReuseCount);
		AbstractCloneable* clone() const override;
	};
}

#endif
