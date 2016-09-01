#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Mocks/MockFeedForwardNetworkTopology.hpp"

using ::testing::Return;
using ::testing::Expectation;

TEST(TopologicalOrderFunction, executeActivation)
{
	MockFeedForwardNetworkTopology FeedForwardNetworkTopology;
	EXPECT_CALL(FeedForwardNetworkTopology, getLayerCount()).WillRepeatedly(Return(3));
	Expectation netInput1 = EXPECT_CALL(FeedForwardNetworkTopology, refreshNetInputsForLayer(1)).Times(1);
	Expectation activation1 = EXPECT_CALL(FeedForwardNetworkTopology, refreshActivationsForLayer(1)).Times(1).After(netInput1);
	Expectation netInput2 = EXPECT_CALL(FeedForwardNetworkTopology, refreshNetInputsForLayer(2)).Times(1).After(activation1);
	Expectation activation2 = EXPECT_CALL(FeedForwardNetworkTopology, refreshActivationsForLayer(2)).Times(1).After(netInput2);

	TopologicalOrder topologicalOrder;

	topologicalOrder.executeActivation(FeedForwardNetworkTopology);
}
