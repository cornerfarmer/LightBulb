// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"


AbstractRecombinationCommand::AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_) {
	recombinationAlgorithm.reset(recombinationAlgorithm_);
}