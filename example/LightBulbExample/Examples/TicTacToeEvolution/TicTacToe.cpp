// Includes
#include "Examples/TicTacToeEvolution/TicTacToe.hpp"
#include "Examples/TicTacToeEvolution/TicTacToeAI.hpp"
#include "LightBulb/Logging/AbstractLogger.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"
#include "LightBulb/Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
//Library includes

using namespace LightBulb;

AbstractIndividual* TicTacToe::createNewIndividual()
{
	return new TicTacToeAI(*options, *this);
}

TicTacToe::TicTacToe(FeedForwardNetworkTopologyOptions& options_, bool isParasiteEnvironment_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToAddAlgorithm_, const std::shared_ptr<LightBulb::AbstractHallOfFameAlgorithm>* hallOfFameToChallengeAlgorithm_)
	: AbstractCoevolutionEnvironment(isParasiteEnvironment_, combiningStrategy_, fitnessFunction_, hallOfFameToAddAlgorithm_, hallOfFameToChallengeAlgorithm_)
{
	options.reset(new FeedForwardNetworkTopologyOptions(options_));
	initialize();
}

TicTacToe::TicTacToe()
{
	initialize();
}

void TicTacToe::initialize()
{
	fields.getEigenValueForEditing().resize(3, 3);
	resetEnvironment();
	stepMode = false;
}

bool TicTacToe::hasGameFinished()
{
	calcWhoHasWon();
	return (illegalMove.getEigenValue() || whoHasWon.getEigenValue() != 0);
}


void TicTacToe::doCompare(AbstractIndividual& obj1, AbstractIndividual& obj2, int round, LightBulb::Scalar<bool>& firstPlayerHasWon)
{
	simulateGame(static_cast<TicTacToeAI&>(obj1), static_cast<TicTacToeAI&>(obj2), round == 1, firstPlayerHasWon);
}

LightBulb::Matrix<int>& TicTacToe::getFields()
{
	return fields;
}

void TicTacToe::startStepMode()
{
	if (!stepMode)
	{
		stepMode = true;
	}
}

void TicTacToe::stopStepMode()
{
	if (stepMode)
	{
		stepMode = false;
		doNextStep.notify_one();
	}
}

std::vector<std::string> TicTacToe::getDataSetLabels() const
{
	auto labels = AbstractCoevolutionEnvironment::getDataSetLabels();
	labels.push_back(std::string(parasiteEnvironment ? DATASET_PARASITE_PREFIX : "") + DATASET_TICTACTOE_RATING);
	return labels;
}

void TicTacToe::nextStep()
{
	if (stepMode)
	{
		doNextStep.notify_all();
	}
}

int TicTacToe::getRoundCount() const
{
	return 2;
}

void TicTacToe::initializeForLearning()
{
}

void TicTacToe::simulateGame(TicTacToeAI& ai1, TicTacToeAI& ai2, bool secondPlayerStarts, LightBulb::Scalar<bool>& firstPlayerHasWon)
{
	ai2.resetNN();
	ai1.resetNN();

	ai1.setTicTacToe(*this);
	ai2.setTicTacToe(*this);

	if (secondPlayerStarts == 0)
		startNewGame(1);
	else
		startNewGame(-1);

	int i;
	for (i = 0; i < 9; i++)
	{
		if (stepMode)
		{
			std::unique_lock<std::mutex> doNextStepMutexLock(doNextStepMutex);
			doNextStep.wait(doNextStepMutexLock);
		}
		if (i % 2 == secondPlayerStarts)
		{
			ai1.doNNCalculation();
		}
		else
		{
			ai2.doNNCalculation();
		}

		//if (isCalculatorType(CT_CPU) && hasGameFinished())
			//break;
	}

	if (isCalculatorType(CT_GPU))
	{
		static viennacl::ocl::kernel& kernel = getKernel("tictactoe_evolution_example", "set_winner", "tictactoe_evolution_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(firstPlayerHasWon.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(whoHasWon.getViennaclValue()),
			viennacl::traits::opencl_handle(illegalMove.getViennaclValue()),
			cl_uint(currentPlayer),
			cl_char(parasiteEnvironment)
		));
	}
	else
	{
		if (illegalMove.getEigenValue())
		{
			if (currentPlayer == -1)
				firstPlayerHasWon.getEigenValueForEditing() = false;
			else
				firstPlayerHasWon.getEigenValueForEditing() = true;
		}
		else
		{
			int w = whoHasWon.getEigenValue();
			if (w == 0) {
				if (parasiteEnvironment)
					firstPlayerHasWon.getEigenValueForEditing() = false;
				else
					firstPlayerHasWon.getEigenValueForEditing() = true;
			}
			else if (w == 1) {
				firstPlayerHasWon.getEigenValueForEditing() = true;
			}
			else if (w == -1) {
				firstPlayerHasWon.getEigenValueForEditing() = false;
			}
		}
	}
}



int TicTacToe::rateIndividual(AbstractIndividual& individual)
{

	int wins = 0;
	int possibleGames = 9 * 7 * 5 * 3;
	possibleGames += 8 * 6 * 4 * 2;

	for (int b = 0; b < 2; b++)
	{
		std::vector<int> decisionNr(b == 0 ? 4 : 4, 0);

		bool decisionCombinationsLeft = true;

		while (decisionCombinationsLeft)
		{
			individual.resetNN();
			startNewGame(b == 0 ? -1 : 1);

			int i;
			for (i = 0; i < 9; i++)
			{
				if (i % 2 == 1 - b)
				{
					individual.doNNCalculation();
				}
				else
				{
					int x = 0, y = 0;
					int freeFieldNr = -1;
					for (y = 0; y < 3; y++)
					{
						for (x = 0; x < 3; x++)
						{
							if (isFree(x, y))
								freeFieldNr++;
							if ((i == 8 && freeFieldNr == 0) || (i != 8 && freeFieldNr == decisionNr[i / 2]))
								goto setField;
						}
					}
				setField:
					setField(x, y);
					currentPlayer *= -1;
				}
				if ( hasGameFinished())
					break;
			}

			calcWhoHasWon();
			if ((currentPlayer == 1 && illegalMove.getEigenValue()) || (whoHasWon.getEigenValue() == 1) || i>8)
				wins++;

			decisionCombinationsLeft = !nextDecisionCombination(decisionNr, b);
		}
	}

	log("Best AI: " + std::to_string(wins) + "/" + std::to_string(possibleGames), LL_MEDIUM);
	if (!learningState->disabledDatasets[std::string(parasiteEnvironment ? DATASET_PARASITE_PREFIX : "") + DATASET_TICTACTOE_RATING])
		learningState->addData(std::string(parasiteEnvironment ? DATASET_PARASITE_PREFIX : "") + DATASET_TICTACTOE_RATING, static_cast<double>(wins) / possibleGames);

	return wins;
}

bool TicTacToe::nextDecisionCombination(std::vector<int>& decisionNr, int b, int level)
{
	bool changeAtThisLevel = true;
	if (level < 3)
		changeAtThisLevel = nextDecisionCombination(decisionNr, b, level + 1);
	if (changeAtThisLevel) {
		decisionNr[level]++;
		if ((decisionNr[level] >= (4 - level) * 2 + 1 && b == 0) || (decisionNr[level] >= (4 - level) * 2 && b == 1))
		{
			decisionNr[level] = 0;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool TicTacToe::isFree(int x, int y)
{
	return fields.getEigenValue()(x, y) == 0;
}

void TicTacToe::startNewGame(int firstPlayer)
{
	resetEnvironment();
	currentPlayer = firstPlayer;
}

void TicTacToe::calcWhoHasWon()
{
	if (isCalculatorType(CT_GPU))
	{
		static viennacl::ocl::kernel& kernel = getKernel("tictactoe_evolution_example", "calc_who_has_won", "tictactoe_evolution_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(whoHasWon.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(fields.getViennaclValue()),
			cl_uint(viennacl::traits::internal_size2(fields.getViennaclValue()))
		));
	}
	else
	{
		if (fields.getEigenValue()(0,0) != 0 && fields.getEigenValue()(0,0) == fields.getEigenValue()(0,1) && fields.getEigenValue()(0,1) == fields.getEigenValue()(0,2))
			whoHasWon.getEigenValueForEditing() = fields.getEigenValue()(0,0);
		else if (fields.getEigenValue()(1,0) != 0 && fields.getEigenValue()(1,0) == fields.getEigenValue()(1,1) && fields.getEigenValue()(1,1) == fields.getEigenValue()(1,2))
			whoHasWon.getEigenValueForEditing() = fields.getEigenValue()(1,0);
		else if (fields.getEigenValue()(2,0) != 0 && fields.getEigenValue()(2,0) == fields.getEigenValue()(2,1) && fields.getEigenValue()(2,1) == fields.getEigenValue()(2,2))
			whoHasWon.getEigenValueForEditing() = fields.getEigenValue()(2,0);

		else if (fields.getEigenValue()(0,0) != 0 && fields.getEigenValue()(0,0) == fields.getEigenValue()(1,0) && fields.getEigenValue()(1,0) == fields.getEigenValue()(2,0))
			whoHasWon.getEigenValueForEditing() = fields.getEigenValue()(0,0);
		else if (fields.getEigenValue()(0,1) != 0 && fields.getEigenValue()(0,1) == fields.getEigenValue()(1,1) && fields.getEigenValue()(1,1) == fields.getEigenValue()(2,1))
			whoHasWon.getEigenValueForEditing() = fields.getEigenValue()(0,1);
		else if (fields.getEigenValue()(0,2) != 0 && fields.getEigenValue()(0,2) == fields.getEigenValue()(1,2) && fields.getEigenValue()(1,2) == fields.getEigenValue()(2,2))
			whoHasWon.getEigenValueForEditing() = fields.getEigenValue()(0,2);

		else if (fields.getEigenValue()(0,0) != 0 && fields.getEigenValue()(0,0) == fields.getEigenValue()(1,1) && fields.getEigenValue()(1,1) == fields.getEigenValue()(2,2))
			whoHasWon.getEigenValueForEditing() = fields.getEigenValue()(0,0);
		else if (fields.getEigenValue()(2,0) != 0 && fields.getEigenValue()(2,0) == fields.getEigenValue()(1,1) && fields.getEigenValue()(1,1) == fields.getEigenValue()(0,2))
			whoHasWon.getEigenValueForEditing() = fields.getEigenValue()(2,0);
		else
			whoHasWon.getEigenValueForEditing() = 0;
	}
}

void TicTacToe::setField(int x, int y)
{
	if (!isFree(x, y))
		illegalMove.getEigenValueForEditing() = true;
	else {
		fields.getEigenValueForEditing()(x, y) = currentPlayer;
		throwEvent(EVT_FIELD_CHANGED, *this);
	}
}

void TicTacToe::setFieldsFromOutput(const LightBulb::Vector<>& output)
{
	if (isCalculatorType(CT_GPU))
	{
		static viennacl::ocl::kernel& kernel = getKernel("tictactoe_evolution_example", "set_fields_from_output", "tictactoe_evolution_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(output.getViennaclValue()),
			viennacl::traits::opencl_handle(fields.getViennaclValueForEditing()),
			cl_uint(viennacl::traits::internal_size2(fields.getViennaclValue())),
			viennacl::traits::opencl_handle(illegalMove.getViennaclValueForEditing()),
			cl_int(currentPlayer)
		));

		currentPlayer *= -1;
		throwEvent(EVT_FIELD_CHANGED, *this);
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			int x = i / 3;
			int y = i % 3;
			if (output.getEigenValue()[i] > 0.5)
			{
				setField(x, y);
				currentPlayer *= -1;
				return;
			}
		}
		illegalMove.getEigenValueForEditing() = true;
		currentPlayer *= -1;
	}

}



void TicTacToe::resetEnvironment()
{
	if (isCalculatorType(CT_GPU))
	{
		static viennacl::ocl::kernel& kernel = getKernel("tictactoe_evolution_example", "reset_environment", "tictactoe_evolution_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(fields.getViennaclValueForEditing()),
			cl_uint(viennacl::traits::internal_size2(fields.getViennaclValue())),
			viennacl::traits::opencl_handle(illegalMove.getViennaclValueForEditing())
		));
	}
	else
	{
		illegalMove.getEigenValueForEditing() = false;
		fields.getEigenValueForEditing().setZero();
	}
	throwEvent(EVT_FIELD_CHANGED, *this);
}


 void TicTacToe::getSight(LightBulb::Vector<>& sight)
{
	if (isCalculatorType(CT_GPU))
	{
		static viennacl::ocl::kernel& kernel = getKernel("tictactoe_evolution_example", "get_sight", "tictactoe_evolution_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(sight.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(fields.getViennaclValue()),
			cl_uint(viennacl::traits::internal_size2(fields.getViennaclValue())),
			cl_int(currentPlayer)
		));
	}
	else
	{
		int sightIndex = 0;
		for (int x = 0; x < fields.getEigenValue().rows(); x++)
		{
			for (int y = 0; y < fields.getEigenValue().cols(); y++)
			{
				int fieldValue = currentPlayer * fields.getEigenValueForEditing()(x, y);
				if (fieldValue == 1)
					sight.getEigenValueForEditing()[sightIndex++] = 1;
				else
					sight.getEigenValueForEditing()[sightIndex++] = 0;
				if (fieldValue == -1)
					sight.getEigenValueForEditing()[sightIndex++] = 1;
				else
					sight.getEigenValueForEditing()[sightIndex++] = 0;
			}
		}
	}
}
