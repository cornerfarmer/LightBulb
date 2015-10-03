// Includes
#include "Learning\AbstractRecombinationCommand.hpp"


AbstractRecombinationCommand::AbstractRecombinationCommand(AbstractRecombination* recombination_) {
	recombination.reset(recombination_);
}