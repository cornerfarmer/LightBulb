// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"

AbstractMutationCommand::AbstractMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, bool enableDebugOutput_)
{
	mutationAlgorithm.reset(mutationAlgorithm_);
	enableDebugOutput = enableDebugOutput_;
}
