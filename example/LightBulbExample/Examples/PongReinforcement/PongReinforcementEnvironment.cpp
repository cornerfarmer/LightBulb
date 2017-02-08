// Includes
#include "Examples/PongReinforcement/PongReinforcementEnvironment.hpp"
#include "LightBulb/Learning/LearningState.hpp"
//Library includes

using namespace LightBulb;

PongReinforcementEnvironment::PongReinforcementEnvironment(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly, double epsilon)
	: AbstractReinforcementEnvironment(options_, epsilonGreedly, epsilon)
{
	watchMode = false;
}

void PongReinforcementEnvironment::doSimulationStep(Scalar<>& reward)
{
	if (game.whoHasWon() != 0 || time >= game.getProperties().maxTime || time == -1)
	{
		time = 0;
		game.reset();
	}

	game.setPlayer(1);
	doNNCalculation();
	game.setPlayer(-1);
	executeCompareAI();
	game.advanceBall(1);

	if (watchMode)
	{
		throwEvent(EVT_FIELD_CHANGED, *this);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	time++;
	if (time >= game.getProperties().maxTime)
		reward = 0;
	else
		reward = game.whoHasWon();
}

void PongReinforcementEnvironment::getNNInput(LightBulb::Vector<>& input)
{
	if (isCalculatorType(CT_GPU))
	{
		
	}
	else
	{
		input.getEigenValueForEditing()[0] = game.getState().ballPosX / game.getProperties().width;
		input.getEigenValueForEditing()[1] = game.getState().ballPosY / game.getProperties().height;
		input.getEigenValueForEditing()[2] = game.getState().ballVelX / game.getProperties().maxBallSpeed;
		input.getEigenValueForEditing()[3] = game.getState().ballVelY / game.getProperties().maxBallSpeed;
		input.getEigenValueForEditing()[4] = game.getState().paddle1Pos / (game.getProperties().height - game.getProperties().paddleHeight);
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
	if (game.getState().ballPosY > game.getState().paddle2Pos + game.getProperties().paddleHeight / 2)
		game.movePaddle(1);
	else
		game.movePaddle(-1);
}

void PongReinforcementEnvironment::initializeForLearning()
{
	AbstractReinforcementEnvironment::initializeForLearning();
	time = -1;
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
		while (game.whoHasWon() == 0 && time < game.getProperties().maxTime)
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
	return game.whoHasWon() != 0 || time >= game.getProperties().maxTime;
}

void PongReinforcementEnvironment::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
{
	AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
	game.setRandomGenerator(randomGenerator_);
}
