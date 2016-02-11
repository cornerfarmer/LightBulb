#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Mocks/MockLayeredNetwork.hpp"

using ::testing::Return;
using ::testing::Expectation;

TEST(TopologicalOrderFunction, executeActivation)
{
	MockLayeredNetwork layeredNetwork;
	EXPECT_CALL(layeredNetwork, getLayerCount()).WillRepeatedly(Return(3));
	Expectation netInput1 = EXPECT_CALL(layeredNetwork, refreshNetInputsForLayer(1)).Times(1);
	Expectation activation1 = EXPECT_CALL(layeredNetwork, refreshActivationsForLayer(1)).Times(1).After(netInput1);
	Expectation netInput2 = EXPECT_CALL(layeredNetwork, refreshNetInputsForLayer(2)).Times(1).After(activation1);
	Expectation activation2 = EXPECT_CALL(layeredNetwork, refreshActivationsForLayer(2)).Times(1).After(netInput2);

	TopologicalOrder topologicalOrder;

	topologicalOrder.executeActivation(layeredNetwork);
}
