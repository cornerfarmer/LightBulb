#pragma once

#ifndef _CONSTANTREUSECOMMAND_H_
#define _CONSTANTREUSECOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractReuseCommand.hpp"

namespace LightBulb
{
	/**
	 * \brief A class to directly reuse the best N individuals.
	 */
	class ConstantReuseCommand : public AbstractReuseCommand
	{
	private:
		/**
		 * \brief The amount of individuals which should be reused.
		 */
		int individualCount;
		/**
		 * \brief Alternative: Holds the percentage of individuals which should be reused.
		 */
		double reusePercentage;
	public:
		virtual ~ConstantReuseCommand() {};
		ConstantReuseCommand() = default;
		ConstantReuseCommand(const ConstantReuseCommand& other) = default;
		/**
		 * \brief Creates a command which reuses a static amount of individuals.
		 * \param reuseSelector_ The reuse selector to use.
		 * \param individualCount_ The amount of individuals which should be reused.
		 */
		ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, int individualCount_);
		/**
		 * \brief Creates a command which reuses a percentage of individuals.
		 * \param reuseSelector_ The reuse selector to use.
		 * \param reusePercentage_ Holds the percentage of individuals which should be reused.
		 */
		ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, double reusePercentage_);
		ConstantReuseCommand(ConstantReuseCommand&& other) noexcept;
		ConstantReuseCommand& operator=(ConstantReuseCommand other);
		friend void swap(ConstantReuseCommand& lhs, ConstantReuseCommand& rhs) noexcept;
		// Inherited:
		void select(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
