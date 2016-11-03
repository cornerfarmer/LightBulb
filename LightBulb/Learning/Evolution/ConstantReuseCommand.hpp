#pragma once

#ifndef _CONSTANTREUSECOMMAND_H_
#define _CONSTANTREUSECOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractReuseCommand.hpp"

namespace LightBulb
{
	/**
	 * \brief A class to directly reuse the best N evolution objects.
	 */
	class ConstantReuseCommand : public AbstractReuseCommand
	{
	private:
		/**
		 * \brief The amount of objects which should be reused.
		 */
		int objectCount;
		/**
		 * \brief Alternative: Holds the percentage of objects which should be reused.
		 */
		double reusePercentage;
	public:
		virtual ~ConstantReuseCommand() {};
		ConstantReuseCommand() = default;
		ConstantReuseCommand(const ConstantReuseCommand& other) = default;
		/**
		 * \brief Creates a command which reuses a static amount of objects.
		 * \param reuseSelector_ The reuse selector to use.
		 * \param objectCount_ The amount of objects which should be reused.
		 */
		ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, int objectCount_);
		/**
		 * \brief Creates a command which reuses a percentage of objects.
		 * \param reuseSelector_ The reuse selector to use.
		 * \param reusePercentage_ Holds the percentage of objects which should be reused.
		 */
		ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, double reusePercentage_);
		ConstantReuseCommand(ConstantReuseCommand&& other) noexcept;
		ConstantReuseCommand& operator=(ConstantReuseCommand other);
		friend void swap(ConstantReuseCommand& lhs, ConstantReuseCommand& rhs) noexcept;
		// Inherited:
		void select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
