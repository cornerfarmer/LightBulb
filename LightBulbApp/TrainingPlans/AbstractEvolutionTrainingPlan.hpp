#pragma once

#ifndef _ABSTRACTEVOLUTIONTRAININGPLAN_H_
#define _ABSTRACTEVOLUTIONTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"
#include "IO/UseParentSerialization.hpp"

// Library includes


// Forward declarations
class AbstractNeuralNetwork;

class AbstractEvolutionTrainingPlan : public AbstractLearningRuleTrainingPlan
{
	
};

USE_PARENT_SERIALIZATION(AbstractEvolutionTrainingPlan, AbstractLearningRuleTrainingPlan);

#endif
