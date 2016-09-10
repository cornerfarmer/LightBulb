#include "TCProblemTeacher.hpp"
#include <Teaching/TeachingLessonBooleanInput.hpp>

using namespace LightBulb;

TCProblemTeacher::TCProblemTeacher(bool calcStrictError, double weightDecayFac_)
	:Teacher(weightDecayFac_)
{
	std::vector<Eigen::MatrixXi> lernExamples(40, Eigen::MatrixXi(4, 4));

	// Ts
	lernExamples[0] << 
		1, 0, 0, 0,
		1, 1, 1, 0,
		1, 0, 0, 0,
		0, 0, 0, 0;

	lernExamples[1] << 
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 1, 0,
		1, 0, 0, 0;

	lernExamples[2] <<
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 1,
		0, 1, 0, 0;

	lernExamples[3] <<
		0, 1, 0, 0,
		0, 1, 1, 1,
		0, 1, 0, 0,
		0, 0, 0, 0;

	//Cs
	lernExamples[4] <<
		1, 1, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0,
		0, 0, 0, 0;

	lernExamples[5] <<
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0;

	lernExamples[6] <<
		0, 0, 1, 1,
		0, 0, 1, 0,
		0, 0, 1, 1,
		0, 0, 0, 0;

	lernExamples[7] <<
		0, 0, 0, 0,
		1, 1, 0, 0,
		1, 0, 0, 0,
		1, 1, 0, 0;

	lernExamples[8] <<
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 1, 0;

	lernExamples[9] <<
		0, 0, 0, 0,
		0, 0, 1, 1,
		0, 0, 1, 0,
		0, 0, 1, 1;

	for (int i = 10; i < 20; i++)
	{
		lernExamples[i] = lernExamples[i - 10].rowwise().reverse();
	}

	for (int i = 20; i < 30; i++)
	{
		lernExamples[i] = lernExamples[i - 10].transpose();
	}

	for (int i = 30; i < 40; i++)
	{
		lernExamples[i] = lernExamples[i - 10].colwise().reverse();
	}

	for (int i = 0; i < 40; i ++)
	{
		std::vector<std::vector<double>> teachingPattern(1, std::vector<double>(16));
		NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(1);
		for (int l = 0; l < 16; l += 1)
		{
			teachingPattern[0][l] = lernExamples[i](l % 4, l / 4);
		}
		(*teachingInput).set(0, 0, (i % 10) >= 4);

		addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput, calcStrictError));
	}
}


