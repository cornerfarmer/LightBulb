// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"

void LightBulb::AbstractMutationAlgorithm::setZigguratGenerator(ZigguratGenerator& newZigguratGenerator)
{
	zigguratGenerator = &newZigguratGenerator;
}
