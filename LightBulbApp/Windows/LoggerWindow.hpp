#pragma once

#ifndef _LOGGERWINDOW_H_
#define _LOGGERWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractWindow.hpp"
#include "LoggerController.hpp"
#include <Logging/AbstractLogger.hpp>

// Forward declarations
class wxRichTextCtrl;

class LoggerWindow : public AbstractWindow
{
private:
	LoggerController* controller;
	wxRichTextCtrl* textBox;
public:
	LoggerWindow(LoggerController* controller_);
	void addLogMessage(std::string message);
};

#endif
