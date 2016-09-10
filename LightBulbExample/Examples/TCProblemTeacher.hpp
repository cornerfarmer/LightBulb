
#pragma once

#ifndef _TCPROBLEMTEACHER_H_
#define _TCPROBLEMTEACHER_H_

#include <Teaching/Teacher.hpp>

class TCProblemTeacher : public LightBulb::Teacher
{
private:
protected:
public:
	TCProblemTeacher(bool calcStrictError, double weightDecayFac_ = 0);
};


#endif
