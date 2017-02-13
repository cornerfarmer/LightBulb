// Includes
#include "Examples/PongReinforcement/PongReinforcementEnvironment.hpp"
#include "LightBulb/Learning/LearningState.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
//Library includes

using namespace LightBulb;

PongReinforcementEnvironment::PongReinforcementEnvironment(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly, double epsilon)
	: AbstractReinforcementEnvironment(options_, epsilonGreedly, epsilon)
{
	watchMode = false;
}

void PongReinforcementEnvironment::doSimulationStep(Scalar<>& reward)
{
	if (isCalculatorType(CT_CPU))
	{
		if (game.whoHasWon() != 0 || time.getEigenValue() >= game.getProperties().maxTime.getEigenValue() || time.getEigenValue() == -1)
		{
			time.getEigenValueForEditing() = 0;
			game.reset();
		}
		game.setPlayer(1);
	}

	doNNCalculation();
	game.setPlayer(-1);
	executeCompareAI();
	game.advanceBall(1);

	if (watchMode)
	{
		throwEvent(EVT_FIELD_CHANGED, *this);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	time.getEigenValueForEditing()++;
	if (time.getEigenValue() >= game.getProperties().maxTime.getEigenValue())
		reward.getEigenValueForEditing() = 0;
	else
		reward.getEigenValueForEditing() = game.whoHasWon();
}

void PongReinforcementEnvironment::getNNInput(LightBulb::Vector<>& input)
{
	if (isCalculatorType(CT_GPU))
	{
		static viennacl::ocl::kernel& kernel = getKernel("pong_reinforcement_example", "get_nn_input", "pong_reinforcement_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(time.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getProperties().maxTime.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getState().ballPosX.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().ballPosY.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().ballVelX.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().ballVelY.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getProperties().ballRad.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getProperties().width.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getProperties().height.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getProperties().maxBallSpeed.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getProperties().minBallSpeed.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getState().paddle1Pos.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().paddle2Pos.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getProperties().paddleHeight.getViennaclValue()),
			cl_float((float)randomGenerator->randDouble()),
			cl_float((float)randomGenerator->randDouble()),
			cl_float((float)randomGenerator->randDouble()),
			cl_float((float)randomGenerator->randDouble()),
			viennacl::traits::opencl_handle(input.getViennaclValueForEditing())
		));

		game.getState().ballPosX.getEigenValue();
		game.getState().ballPosY.getEigenValue();
	}
	else
	{
		input.getEigenValueForEditing()[0] = game.getState().ballPosX.getEigenValue() / game.getProperties().width.getEigenValue();
		input.getEigenValueForEditing()[1] = game.getState().ballPosY.getEigenValue() / game.getProperties().height.getEigenValue();
		input.getEigenValueForEditing()[2] = game.getState().ballVelX.getEigenValue() / game.getProperties().maxBallSpeed.getEigenValue();
		input.getEigenValueForEditing()[3] = game.getState().ballVelY.getEigenValue() / game.getProperties().maxBallSpeed.getEigenValue();
		input.getEigenValueForEditing()[4] = game.getState().paddle1Pos.getEigenValue() / (game.getProperties().height.getEigenValue() - game.getProperties().paddleHeight.getEigenValue());
		input.getEigenValueForEditing()[5] = 0; // game.getState().paddle2Pos / (game.getProperties().height - game.getProperties().paddleHeight);
	}
}

void PongReinforcementEnvironment::interpretNNOutput(LightBulb::Vector<char>& output)
{
	if (isCalculatorType(CT_GPU))
	{

	}
	else
	{
		if (output.getEigenValue()[0])
			game.movePaddle(1);
		else if ((output.getEigenValue().size() > 1 && output.getEigenValue()[1]) || (output.getEigenValue().size() == 1 && !output.getEigenValue()[0]))
			game.movePaddle(-1);
	}
}


void PongReinforcementEnvironment::executeCompareAI()
{
	if (isCalculatorType(CT_GPU))
	{

	}
	else
	{
		if (game.getState().ballPosY.getEigenValue() > game.getState().paddle2Pos.getEigenValue() + game.getProperties().paddleHeight.getEigenValue() / 2)
			game.movePaddle(1);
		else
			game.movePaddle(-1);
	}
}

void PongReinforcementEnvironment::initializeForLearning()
{
	AbstractReinforcementEnvironment::initializeForLearning();
	time.getEigenValueForEditing() = -1;
}


int PongReinforcementEnvironment::rate()
{
	PongGame tmp = game;
	int wins = 0;
	int matchCount = 100;
	for (int i = 0; i < matchCount; i++)
	{
		game.reset();

		double time = 0;
		while (game.whoHasWon() == 0 && time < game.getProperties().maxTime.getEigenValue())
		{
			game.setPlayer(1);
			doNNCalculation();
			game.setPlayer(-1);
			executeCompareAI();
			game.advanceBall(1);

			time++;
		}

		if (game.whoHasWon() == 1 || game.whoHasWon() == 0)
			wins++;
	}

	if (!learningState->disabledDatasets[DATASET_PONG_RATING])
		learningState->addData(DATASET_PONG_RATING, static_cast<double>(wins) / matchCount);
	game = tmp;
	return wins;
}


std::vector<std::string> PongReinforcementEnvironment::getDataSetLabels() const
{
	auto labels = AbstractReinforcementEnvironment::getDataSetLabels();
	labels.push_back(DATASET_PONG_RATING);
	return labels;
}

bool PongReinforcementEnvironment::isTerminalState()
{
	return game.whoHasWon() != 0 || time.getEigenValue() >= game.getProperties().maxTime.getEigenValue();
}

void PongReinforcementEnvironment::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
{
	AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
	game.setRandomGenerator(randomGenerator_);
}
