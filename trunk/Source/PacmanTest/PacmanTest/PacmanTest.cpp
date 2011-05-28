// PacmanTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Window.h"
#include "SDL.h"
#include "ScreenManager.h"
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void Execute(void)
{
	Window* w = new Window("Pacman", 480, 640);
	//esperar para cerrar
	ScreenManager screenManager(w, "Images/fondo.bmp");
	screenManager.startGame();
	delete w;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Execute();
	int leaks = _CrtDumpMemoryLeaks();
}