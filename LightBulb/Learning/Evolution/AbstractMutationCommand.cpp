// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"

AbstractMutationCommand::AbstractMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, bool enableDebugOutput_)
{
	mutationAlgorithm.reset(mutationAlgorithm_);
	mutationSelector.reset(mutationSelector_);
	enableDebugOutput = enableDebugOutput_;
}
