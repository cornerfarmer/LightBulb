#pragma once

#ifndef _TICTACTOEGAMEFACTORY_H_
#define _TICTACTOEGAMEFACTORY_H_

// Includes
#include <Windows/AbstractCustomSubAppFactory.hpp>

// Forward declarations
class TrainingPlanRepository;

class TicTacToeGameFactory : public AbstractCustomSubAppFactory
{
protected:
public:
	AbstractCustomSubApp* createCustomSupApp(AbstractMainApp* mainApp, AbstractTrainingPlan* trainingPlan, AbstractWindow* parent) override;
	std::string getLabel() override;
};

#endif
