// Includes
#include "LightBulb/Learning/Evolution/TeachingEvolutionEnvironment.hpp"
#include "LightBulb/Learning/Evolution/TeachedIndividual.hpp"
#include "LightBulb/Learning/LearningState.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"

//Library includes

namespace LightBulb
{
	TeachingEvolutionEnvironment::TeachingEvolutionEnvironment() = default;

	TeachingEvolutionEnvironment::~TeachingEvolutionEnvironment() = default;

	AbstractIndividual* TeachingEvolutionEnvironment::createNewIndividual()
	{
		return new TeachedIndividual(*this, *networkOptions);
	}

	TeachingEvolutionEnvironment::TeachingEvolutionEnvironment(AbstractTeacher* teacher_, FeedForwardNetworkTopologyOptions& networkOptions_)
	{
		teacher = teacher_;
		networkOptions.reset(new FeedForwardNetworkTopologyOptions(networkOptions_));
	}

	void TeachingEvolutionEnvironment::doSimulationStep()
	{
		// Just recalculate the current total error values of all individuals
		for (auto teachedIndividual = individuals.begin(); teachedIndividual != individuals.end(); teachedIndividual++)
		{
			(*teachedIndividual)->doNNCalculation();
		}

		const Highscore& highscore = getHighscoreList();

		if (learningState && !learningState->disabledDatasets[DATASET_TEACHING_ERROR])
			learningState->addData(DATASET_TEACHING_ERROR, static_cast<TeachedIndividual*>(highscore.front().second)->getCurrentTeachingError());

		if (learningState && !learningState->disabledDatasets[DATASET_WEIGHTDECAY_ERROR])
			learningState->addData(DATASET_WEIGHTDECAY_ERROR, static_cast<TeachedIndividual*>(highscore.front().second)->getCurrentWeightDecayError());
	}

	std::vector<std::string> TeachingEvolutionEnvironment::getDataSetLabels() const
	{
		auto labels = AbstractEvolutionEnvironment::getDataSetLabels();
		labels.push_back(DATASET_TEACHING_ERROR);
		labels.push_back(DATASET_WEIGHTDECAY_ERROR);
		return labels;
	}

	void TeachingEvolutionEnvironment::getFitness(const AbstractIndividual& individual, LightBulb::Scalar<>& fitness) const
	{
		// Just return the total error of the individual (negate it, so the error 0 is the maximum)
		fitness.getEigenValueForEditing() = -static_cast<const TeachedIndividual&>(individual).getCurrentTotalError();
	}


	AbstractTeacher& TeachingEvolutionEnvironment::getTeacher() const
	{
		return *teacher;
	}
}
