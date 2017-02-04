#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockMutationSelector.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/TeachingEvolutionEnvironment.hpp>
#include <Mocks/MockTeacher.hpp>
#include <Mocks/MockNeuronDescriptionFactory.hpp>
#include "Mocks/MockRandomGenerator.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"

using namespace LightBulb;

class TeachedEvolutionTest : public testing::Test {
public:
	TeachingEvolutionEnvironment* teachingEvolutionEnvironment;
	MockTeacher teacher;
	FeedForwardNetworkTopologyOptions options;
	MockRandomGenerator randomGenerator;
	void SetUp() {
		
		options.descriptionFactory = new MockNeuronDescriptionFactory();
		options.neuronsPerLayerCount.push_back(2);
		options.neuronsPerLayerCount.push_back(1);
		teachingEvolutionEnvironment = new TeachingEvolutionEnvironment(&teacher, options);
		teachingEvolutionEnvironment->setRandomGenerator(randomGenerator);
		EXPECT_CALL(randomGenerator, randDouble(testing::_, testing::_)).WillRepeatedly(testing::Return(0.1));
	}

	virtual ~TeachedEvolutionTest()
	{
		//delete teachingEvolutionEnvironment;
	}
};

TEST_F(TeachedEvolutionTest, doSimulationStep)
{
	AbstractIndividual* individual = teachingEvolutionEnvironment->addNewIndividual(true);

	EXPECT_CALL(teacher, getTeachingError(testing::Ref(individual->getNeuralNetwork()), testing::_)).WillOnce(testing::Return(5));
	EXPECT_CALL(teacher, getWeightDecayError(testing::Ref(individual->getNeuralNetwork()))).WillOnce(testing::Return(3));

	teachingEvolutionEnvironment->doSimulationStep();

	Scalar<> result;
	teachingEvolutionEnvironment->getFitness(*individual, result);
	EXPECT_EQ(-8, result.getEigenValue());
}
