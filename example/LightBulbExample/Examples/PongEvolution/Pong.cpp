// Includes
#include "Examples/PongEvolution/Pong.hpp"
#include "Examples/PongEvolution/PongAI.hpp"
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"
#include "LightBulb/Logging/AbstractLogger.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
//Library includes


using namespace LightBulb;

AbstractIndividual* Pong::createNewIndividual()
{
	return new PongAI(*options, *this);
}

Pong::Pong(FeedForwardNetworkTopologyOptions& options_, bool isParasiteEnvironment_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToAddAlgorithm_, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToChallengeAlgorithm_)
	: AbstractCoevolutionEnvironment(isParasiteEnvironment_, combiningStrategy_, fitnessFunction_, hallOfFameToAddAlgorithm_, hallOfFameToChallengeAlgorithm_)
{
	options.reset(new FeedForwardNetworkTopologyOptions(options_));
	watchMode = false;
}

void Pong::doCompare(AbstractIndividual& obj1, AbstractIndividual& obj2, int round, Scalar<bool>& firstPlayerHasWon)
{
	return simulateGame(static_cast<PongAI&>(obj1), static_cast<PongAI&>(obj2), firstPlayerHasWon);
}


std::vector<std::string> Pong::getDataSetLabels() const
{
	auto labels = AbstractCoevolutionEnvironment::getDataSetLabels();
	labels.push_back(std::string(parasiteEnvironment ? DATASET_PARASITE_PREFIX : "") + DATASET_PONG_RATING);
	return labels;
}


int Pong::getRoundCount() const
{
	return 1;
}


void Pong::simulateGame(PongAI& ai1, PongAI& ai2, Scalar<bool>& firstPlayerHasWon)
{
	ai2.resetNN();
	ai1.resetNN();

	ai1.setPong(*this);
	ai2.setPong(*this);

	startNewGame();

	double time = 0;
	while (game.whoHasWon() == 0 && time < game.getProperties().maxTime.getEigenValue())
	{
		game.setPlayer(1);
		ai1.doNNCalculation();
		game.setPlayer(-1);
		ai2.doNNCalculation();
		game.advanceBall(1);

		if (watchMode)
		{
			throwEvent(EVT_FIELD_CHANGED, *this);
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		time++;
	}

	if (game.whoHasWon() == 0) {
		if (parasiteEnvironment)
			firstPlayerHasWon.getEigenValueForEditing() = false;
		else
			firstPlayerHasWon.getEigenValueForEditing() = true;
	}
	else
		firstPlayerHasWon.getEigenValueForEditing() = game.whoHasWon() > 0;
}

void Pong::executeCompareAI()
{
	if (game.getState().ballPosY.getEigenValue() > game.getState().paddle2Pos.getEigenValue() + game.getProperties().paddleHeight.getEigenValue() / 2)
		game.movePaddle(1);
	else
		game.movePaddle(-1);
}


int Pong::rateIndividual(AbstractIndividual& individual)
{

	static_cast<PongAI&>(individual).setPong(*this);
	int wins = 0;
	int matchCount = 100;
	for (int i = 0; i < matchCount; i++)
	{
		individual.resetNN();

		startNewGame();

		double time = 0;
		while (game.whoHasWon() == 0 && time < game.getProperties().maxTime.getEigenValue())
		{
			game.setPlayer(1);
			individual.doNNCalculation();
			game.setPlayer(-1);
			executeCompareAI();
			game.advanceBall(1);

			/*if (watchMode)
			{
				throwEvent(EVT_FIELD_CHANGED, this);
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}*/
			time++;
		}

		if (game.whoHasWon() == 1 || game.whoHasWon() == 0)
			wins++;
	}
	log("Best AI: " + std::to_string(wins) + "/" + std::to_string(matchCount), LL_MEDIUM);
	if (!learningState->disabledDatasets[std::string(parasiteEnvironment ? DATASET_PARASITE_PREFIX : "") + DATASET_PONG_RATING])
		learningState->addData(std::string(parasiteEnvironment ? DATASET_PARASITE_PREFIX : "") + DATASET_PONG_RATING, static_cast<double>(wins) / matchCount);

	return wins;
}


void Pong::startNewGame()
{
	resetEnvironment();
}

void Pong::resetEnvironment()
{
	game.reset();
}

void Pong::getNNInput(LightBulb::Vector<>& input)
{
	input.getEigenValueForEditing()[0] = game.getState().ballPosX.getEigenValue() / game.getProperties().width.getEigenValue();
	if (game.getPlayer() == -1)
		input.getEigenValueForEditing()[0] = 1 - input.getEigenValue()[0];
	input.getEigenValueForEditing()[1] = game.getState().ballPosY.getEigenValue() / game.getProperties().height.getEigenValue();
	input.getEigenValueForEditing()[2] = game.getPlayer() * game.getState().ballVelX.getEigenValue() / game.getProperties().maxBallSpeed.getEigenValue();
	input.getEigenValueForEditing()[3] = game.getState().ballVelY.getEigenValue() / game.getProperties().maxBallSpeed.getEigenValue();
	if (game.getPlayer() == 1)
	{
		input.getEigenValueForEditing()[4] = game.getState().paddle1Pos.getEigenValue() / (game.getProperties().height.getEigenValue() - game.getProperties().paddleHeight.getEigenValue());
		input.getEigenValueForEditing()[5] = game.getState().paddle2Pos.getEigenValue() / (game.getProperties().height.getEigenValue() - game.getProperties().paddleHeight.getEigenValue());
	}
	else
	{
		input.getEigenValueForEditing()[5] = game.getState().paddle1Pos.getEigenValue() / (game.getProperties().height.getEigenValue() - game.getProperties().paddleHeight.getEigenValue());
		input.getEigenValueForEditing()[4] = game.getState().paddle2Pos.getEigenValue() / (game.getProperties().height.getEigenValue() - game.getProperties().paddleHeight.getEigenValue());
	}
}


void Pong::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
{
	AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
	game.setRandomGenerator(randomGenerator_);
}
