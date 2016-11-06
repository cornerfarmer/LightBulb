#pragma once

#ifndef _CONSTANTRECOMBINATIONCOMMAND_H_
#define _CONSTANTRECOMBINATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "Function/RandomFunction/RankBasedRandomFunction.hpp"

namespace LightBulb
{
	/**
	* \brief Recombines a constant amount of objects.
	*/
	class ConstantRecombinationCommand : public AbstractRecombinationCommand
	{
	private:
		/**
		* \brief The amount of objects which should be recombined.
		*/
		int objectCount;
		/**
		* \brief Alternative: The percentage of objects which should be recombined.
		*/
		double recombinationPercentage;
	public:
		ConstantRecombinationCommand() = default;
		ConstantRecombinationCommand(const ConstantRecombinationCommand& other) = default;
		/**
		 * \brief Creates a command which combines a static amount of objects.
		 * \param recombinationAlgorithm_ The recombination algorithm to use.
		 * \param recombinationSelector_ The recombination selector to use.
		 * \param objectCount_ The amount of objects which should be recombined.
		 */
		ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, int objectCount_);
		/**
		 * \brief Creates a command which combines a percentage of objects.
		 * \param recombinationAlgorithm_ The recombination algorithm to use.
		 * \param recombinationSelector_ The recombination selector to use.
		 * \param recombinationPercentage_ The percentage of objects which should be recombined.
		 */
		ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, double recombinationPercentage_);
		ConstantRecombinationCommand(ConstantRecombinationCommand&& other) noexcept;
		ConstantRecombinationCommand& operator=(ConstantRecombinationCommand other);
		friend void swap(ConstantRecombinationCommand& lhs, ConstantRecombinationCommand& rhs) noexcept;
		// Inherited:
		void select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
