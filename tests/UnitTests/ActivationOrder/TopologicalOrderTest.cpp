#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "Mocks/MockFeedForwardNetworkTopology.hpp"

using testing::Return;
using testing::Expectation;
using namespace LightBulb;

TEST(TopologicalOrderFunction, executeActivation)
{
	MockFeedForwardNetworkTopology feedForwardNetworkTopology;
	EXPECT_CALL(feedForwardNetworkTopology, getLayerCount()).WillRepeatedly(Return(3));
	Expectation netInput1 = EXPECT_CALL(feedForwardNetworkTopology, refreshNetInputsForLayer(1, nullptr)).Times(1);
	Expectation activation1 = EXPECT_CALL(feedForwardNetworkTopology, refreshActivationsForLayer(1)).Times(1).After(netInput1);
	Expectation netInput2 = EXPECT_CALL(feedForwardNetworkTopology, refreshNetInputsForLayer(2, nullptr)).Times(1).After(activation1);
	Expectation activation2 = EXPECT_CALL(feedForwardNetworkTopology, refreshActivationsForLayer(2)).Times(1).After(netInput2);

	TopologicalOrder topologicalOrder;

	topologicalOrder.executeActivation(feedForwardNetworkTopology);
}
