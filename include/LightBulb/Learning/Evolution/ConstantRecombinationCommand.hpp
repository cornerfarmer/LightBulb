#pragma once

#ifndef _CONSTANTRECOMBINATIONCOMMAND_H_
#define _CONSTANTRECOMBINATIONCOMMAND_H_

// Library Includes

// Includes
#include "LightBulb/Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "LightBulb/Function/RandomFunction/RankBasedRandomFunction.hpp"

namespace LightBulb
{
	/**
	* \brief Recombines a constant amount of individuals.
	*/
	class ConstantRecombinationCommand : public AbstractRecombinationCommand
	{
	private:
		/**
		* \brief The amount of individuals which should be recombined.
		*/
		int individualCount;
		/**
		* \brief Alternative: The percentage of individuals which should be recombined.
		*/
		double recombinationPercentage;
	public:
		ConstantRecombinationCommand() = default;
		ConstantRecombinationCommand(const ConstantRecombinationCommand& other) = default;
		/**
		 * \brief Creates a command which combines a static amount of individuals.
		 * \param recombinationAlgorithm_ The recombination algorithm to use.
		 * \param recombinationSelector_ The recombination selector to use.
		 * \param individualCount_ The amount of individuals which should be recombined.
		 */
		ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, int individualCount_);
		/**
		 * \brief Creates a command which combines a percentage of individuals.
		 * \param recombinationAlgorithm_ The recombination algorithm to use.
		 * \param recombinationSelector_ The recombination selector to use.
		 * \param recombinationPercentage_ The percentage of individuals which should be recombined.
		 */
		ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, double recombinationPercentage_);
		ConstantRecombinationCommand(ConstantRecombinationCommand&& other) noexcept;
		ConstantRecombinationCommand& operator=(ConstantRecombinationCommand other);
		friend void swap(ConstantRecombinationCommand& lhs, ConstantRecombinationCommand& rhs) noexcept;
		// Inherited:
		void select(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
