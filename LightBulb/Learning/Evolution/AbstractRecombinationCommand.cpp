// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"


AbstractRecombinationCommand::AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, bool enableDebugOutput_) {
	recombinationAlgorithm.reset(recombinationAlgorithm_);
	recombinationSelector.reset(recombinationSelector_);
	enableDebugOutput = enableDebugOutput_;
}
