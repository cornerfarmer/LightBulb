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
	inSimulationPhase = false;
}

void PongReinforcementEnvironment::doSimulationStep(Scalar<>& reward)
{
	inSimulationPhase = true;
	rewardTmp = &reward;
	if (isCalculatorType(CT_CPU))
	{
		if (game.whoHasWon() != 0 || time.getEigenValue() >= game.getProperties().maxTime.getEigenValue() || time.getEigenValue() == -1)
		{
			time.getEigenValueForEditing() = 0;
			game.reset();
		}
		else
		{
			// Keep random numbers synced between cpu and gpu computation
			for (int i = 0; i < 4; i++)
				randomGenerator->randFloat();
		}
		game.setPlayer(1);
	}

	doNNCalculation();
	if (isCalculatorType(CT_CPU))
	{
		game.setPlayer(-1);
		executeCompareAI();
		game.advanceBall(1);
	}

	if (watchMode)
	{
		throwEvent(EVT_FIELD_CHANGED, *this);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}

	if (isCalculatorType(CT_CPU))
	{
		time.getEigenValueForEditing()++;
		reward.getEigenValueForEditing() = game.whoHasWon();
	}
	inSimulationPhase = false;
}

void PongReinforcementEnvironment::getNNInput(LightBulb::Vector<>& input)
{
	if (isCalculatorType(CT_GPU))
	{
		if (inSimulationPhase)
		{
			static viennacl::ocl::kernel& kernel = getKernel("pong_reinforcement_example", "get_nn_input", "pong_reinforcement_example.cl");

			float rand1 = randomGenerator->randFloat();
			float rand2 = randomGenerator->randFloat();
			float rand3 = randomGenerator->randFloat();
			float rand4 = randomGenerator->randFloat();

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
				cl_float(rand1),
				cl_float(rand2),
				cl_float(rand3),
				cl_float(rand4),
				viennacl::traits::opencl_handle(input.getViennaclValueForEditing()),
				viennacl::traits::opencl_handle(game.getPlayer().getViennaclValueForEditing())
			));
		
		}
		else
		{
			static viennacl::ocl::kernel& kernel = getKernel("pong_reinforcement_example", "get_nn_input_only", "pong_reinforcement_example.cl");

			viennacl::ocl::enqueue(kernel(
				viennacl::traits::opencl_handle(game.getState().ballPosX.getViennaclValue()),
				viennacl::traits::opencl_handle(game.getState().ballPosY.getViennaclValue()),
				viennacl::traits::opencl_handle(game.getState().ballVelX.getViennaclValue()),
				viennacl::traits::opencl_handle(game.getState().ballVelY.getViennaclValue()),
				viennacl::traits::opencl_handle(game.getProperties().width.getViennaclValue()),
				viennacl::traits::opencl_handle(game.getProperties().height.getViennaclValue()),
				viennacl::traits::opencl_handle(game.getProperties().maxBallSpeed.getViennaclValue()),
				viennacl::traits::opencl_handle(game.getState().paddle1Pos.getViennaclValue()),
				viennacl::traits::opencl_handle(game.getState().paddle2Pos.getViennaclValue()),
				viennacl::traits::opencl_handle(game.getProperties().paddleHeight.getViennaclValue()),
				viennacl::traits::opencl_handle(input.getViennaclValueForEditing())
			));
		}
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
		static viennacl::ocl::kernel& kernel = getKernel("pong_reinforcement_example", "interpret_nn_output", "pong_reinforcement_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(time.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().ballPosX.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().ballPosY.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().ballVelX.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().ballVelY.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getProperties().ballRad.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getProperties().width.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getProperties().height.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getProperties().maxBallSpeed.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getState().paddle1Pos.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().paddle2Pos.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getProperties().paddleSpeed.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getProperties().paddleHeight.getViennaclValue()),
			viennacl::traits::opencl_handle(output.getViennaclValue()),
			cl_uint(output.getViennaclValue().size()),
			viennacl::traits::opencl_handle(game.getPlayer().getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getProperties().speedIncreaseFac.getViennaclValue()),
			viennacl::traits::opencl_handle(rewardTmp->getViennaclValueForEditing())
		));
		
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
	if (game.getState().ballPosY.getEigenValue() > game.getState().paddle2Pos.getEigenValue() + game.getProperties().paddleHeight.getEigenValue() / 2)
		game.movePaddle(1);
	else
		game.movePaddle(-1);
}

void PongReinforcementEnvironment::initializeForLearning()
{
	AbstractReinforcementEnvironment::initializeForLearning();
	time.getEigenValueForEditing() = -1;
}


std::vector<std::string> PongReinforcementEnvironment::getDataSetLabels() const
{
	auto labels = AbstractReinforcementEnvironment::getDataSetLabels();
	return labels;
}

void PongReinforcementEnvironment::isTerminalState(Scalar<char>& isTerminalState)
{
	if (isCalculatorType(CT_GPU)) 
	{
		static viennacl::ocl::kernel& kernel = getKernel("pong_reinforcement_example", "is_terminal_state", "pong_reinforcement_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(time.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getProperties().maxTime.getViennaclValue()),
			viennacl::traits::opencl_handle(game.getState().ballPosX.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getProperties().ballRad.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getProperties().width.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(game.getState().ballVelX.getViennaclValueForEditing()),
			viennacl::traits::opencl_handle(isTerminalState.getViennaclValueForEditing())
		));
	}
	else
	{
		isTerminalState.getEigenValueForEditing() = game.whoHasWon() != 0 || time.getEigenValue() >= game.getProperties().maxTime.getEigenValue();
	}
}

void PongReinforcementEnvironment::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
{
	AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
	game.setRandomGenerator(randomGenerator_);
}
