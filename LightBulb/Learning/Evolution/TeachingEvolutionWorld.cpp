// Includes
#include "Learning/Evolution/TeachingEvolutionWorld.hpp"
#include "Learning/Evolution/TeachedEvolutionObject.hpp"
//Library includes
#include <iostream>

AbstractEvolutionObject* TeachingEvolutionWorld::createNewObject()
{
	return new TeachedEvolutionObject(this, networkOptions);
}

TeachingEvolutionWorld::TeachingEvolutionWorld(Teacher* teacher_, LayeredNetworkOptions& networkOptions_)
{
	teacher = teacher_;
	networkOptions = networkOptions_;
}

void TeachingEvolutionWorld::doSimulationStep(EvolutionLearningRule& learningRule)
{
	// Just recalculate the current total error values of all objects
	for (auto teachedEvolutionObject = objects.begin(); teachedEvolutionObject != objects.end(); teachedEvolutionObject++)
	{
		(*teachedEvolutionObject)->doNNCalculation(learningRule);
	}
}

double TeachingEvolutionWorld::getScore(AbstractEvolutionObject* object)
{
	// Just return the total error of the object (negate it, so the error 0 is the maximum)
	return -static_cast<TeachedEvolutionObject*>(object)->getCurrentTotalError();
}


Teacher* TeachingEvolutionWorld::getTeacher()
{
	return teacher;
}
