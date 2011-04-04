#include <stdio.h>
#include <string> 
#pragma once

class ScreenLogger
{
	private:
		static ScreenLogger* instance;
		ScreenLogger();
		~ScreenLogger();
	public:
		static ScreenLogger* getInstance(void);
		void logIn(std::string msg);
};