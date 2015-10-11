// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"

AbstractMutationCommand::AbstractMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_)
{
	mutationAlgorithm.reset(mutationAlgorithm_);
}