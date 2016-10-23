// Includes
#include "Learning/Evolution/TeachingEvolutionWorld.hpp"
#include "Learning/Evolution/TeachedEvolutionObject.hpp"
//Library includes
#include <iostream>

namespace LightBulb
{
	AbstractEvolutionObject* TeachingEvolutionWorld::createNewObject()
	{
		return new TeachedEvolutionObject(*this, networkOptions);
	}

	TeachingEvolutionWorld::TeachingEvolutionWorld(AbstractTeacher* teacher_, FeedForwardNetworkTopologyOptions& networkOptions_)
	{
		teacher = teacher_;
		networkOptions = networkOptions_;
	}

	bool TeachingEvolutionWorld::doSimulationStep()
	{
		// Just recalculate the current total error values of all objects
		for (auto teachedEvolutionObject = objects.begin(); teachedEvolutionObject != objects.end(); teachedEvolutionObject++)
		{
			(*teachedEvolutionObject)->doNNCalculation();
		}

		const Highscore& highscore = getHighscoreList();

		if (learningState && !learningState->disabledDatasets[DATASET_TEACHING_ERROR])
			learningState->addData(DATASET_TEACHING_ERROR, static_cast<TeachedEvolutionObject*>(highscore.front().second)->getCurrentTeachingError());

		if (learningState && !learningState->disabledDatasets[DATASET_WEIGHTDECAY_ERROR])
			learningState->addData(DATASET_WEIGHTDECAY_ERROR, static_cast<TeachedEvolutionObject*>(highscore.front().second)->getCurrentWeightDecayError());

		return false;
	}

	std::vector<std::string> TeachingEvolutionWorld::getDataSetLabels() const
	{
		auto labels = AbstractEvolutionWorld::getDataSetLabels();
		labels.push_back(DATASET_TEACHING_ERROR);
		labels.push_back(DATASET_WEIGHTDECAY_ERROR);
		return labels;
	}

	double TeachingEvolutionWorld::getScore(const AbstractEvolutionObject& object) const
	{
		// Just return the total error of the object (negate it, so the error 0 is the maximum)
		return -static_cast<const TeachedEvolutionObject&>(object).getCurrentTotalError();
	}


	AbstractTeacher& TeachingEvolutionWorld::getTeacher() const
	{
		return *teacher;
	}
}
