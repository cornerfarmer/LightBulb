#pragma once

#ifndef _APP_H_
#define _APP_H_

#include <wx/wxprec.h>

class App : public wxApp
{
public:
	virtual bool OnInit();
	void OnUnhandledException();
	bool OnExceptionInMainLoop();
};

#endif
