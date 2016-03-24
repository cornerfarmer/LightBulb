// Includes
#include "Teaching/ExampleTrainingPlan.hpp"

void ExampleTrainingPlan::run()
{

}

std::string ExampleTrainingPlan::getName()
{
	return "ExampleTrainingPlan";
}

std::string ExampleTrainingPlan::getDescription()
{
	return "Bla bla bla!";
}

std::string ExampleTrainingPlan::getLearningRateName()
{
	return "Backpropagation";
}

AbstractTrainingPlan* ExampleTrainingPlan::getCopy()
{
	return new ExampleTrainingPlan();
}
