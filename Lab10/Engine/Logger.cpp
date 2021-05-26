/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Logger.cpp
Purpose: This is source for the Logger Module.
Project: CS230
Author: Kevin Wright
Creation date: 3/17/2020
-----------------------------------------------------------------*/

#include <iostream>    // cout

#include "Logger.h"

Logger::Logger(Severity severity, bool useConsole) : outStream("Trace.log"), startTime(std::chrono::system_clock::now()) {
	minLevel = severity;
	if (useConsole == true) {
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

void Logger::Log(Logger::Severity severity, std::string message) {
	if (severity >= minLevel) {
		outStream.precision(4);
		outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";

		switch (severity) {
		case Severity::Verbose:
			outStream << "Verb \t";
			break;
		case Severity::Debug:
			outStream << "Debug\t";
			break;
		case Severity::Error:
			outStream << "Error\t";
			break;
		case Severity::Event:
			outStream << "Event\t";
			break;
		}
		outStream << message;

#ifdef _DEBUG
		outStream << std::endl;
#else
		outStream << '\n';
#endif
	}
}