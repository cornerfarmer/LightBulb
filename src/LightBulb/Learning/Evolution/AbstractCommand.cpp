// Includes
#include "Learning/Evolution/AbstractCommand.hpp"
#include "AbstractIndividual.hpp"
#include <Logging/AbstractLogger.hpp>

namespace LightBulb
{
	AbstractIndividual* AbstractCommand::getUnusedIndividual(AbstractIndividual& usedIndividual, std::vector<AbstractIndividual*>& notUsedIndividuals, bool addToWorld) const
	{
		if (notUsedIndividuals.empty())
		{
			return usedIndividual.clone(addToWorld);
		}
		else
		{
			AbstractIndividual* notUsedIndividual = notUsedIndividuals.back();
			notUsedIndividuals.pop_back();
			notUsedIndividual->copyPropertiesFrom(usedIndividual);
			return notUsedIndividual;
		}
	}

	void swap(AbstractCommand& lhs, AbstractCommand& rhs) noexcept
	{
		using std::swap;
	}
}
