// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"


AbstractRecombinationCommand::AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, bool enableDebugOutput_) {
	recombinationAlgorithm.reset(recombinationAlgorithm_);
	enableDebugOutput = enableDebugOutput_;
}
