// Includes
#include "LightBulb/Learning/Evolution/TeachingEvolutionEnvironment.hpp"
#include "LightBulb/Learning/Evolution/TeachedIndividual.hpp"
//Library includes
#include <iostream>

namespace LightBulb
{
	AbstractIndividual* TeachingEvolutionEnvironment::createNewIndividual()
	{
		return new TeachedIndividual(*this, networkOptions);
	}

	TeachingEvolutionEnvironment::TeachingEvolutionEnvironment(AbstractTeacher* teacher_, FeedForwardNetworkTopologyOptions& networkOptions_)
	{
		teacher = teacher_;
		networkOptions = networkOptions_;
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

	double TeachingEvolutionEnvironment::getFitness(const AbstractIndividual& individual) const
	{
		// Just return the total error of the individual (negate it, so the error 0 is the maximum)
		return -static_cast<const TeachedIndividual&>(individual).getCurrentTotalError();
	}


	AbstractTeacher& TeachingEvolutionEnvironment::getTeacher() const
	{
		return *teacher;
	}
}
