#include "stdafx.h"
#include "ScreenLogger.h"
#include <string.h>
#include <iostream>

ScreenLogger* ScreenLogger::instance = 0;

ScreenLogger::ScreenLogger()
{
}

ScreenLogger::~ScreenLogger()
{
}

ScreenLogger* ScreenLogger::getInstance()
{
	if( ScreenLogger::instance == 0 )
	{
		instance = new ScreenLogger();
	}
	
	return instance;

}

void ScreenLogger::logIn(std::string msg)
{
	std::cout << msg;
}