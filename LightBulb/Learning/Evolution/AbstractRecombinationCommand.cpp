// Includes
#include "Learning\Evolution\AbstractRecombinationCommand.hpp"


AbstractRecombinationCommand::AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombination_) {
	recombination.reset(recombination_);
}