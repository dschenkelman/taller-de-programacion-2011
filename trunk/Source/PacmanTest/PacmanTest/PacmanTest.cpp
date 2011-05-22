// PacmanTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Window.h"
#include "SDL.h"
#include "ScreenManager.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Window* w = new Window("Pacman", 480, 640);
	//esperar para cerrar
	SDL_Event e;
	bool running = true;
	Uint32 period = 1000.0 / 60;
	ScreenManager screenManager(w, "Images/fondo.bmp");
 
	while(running) 
	{
		SDL_Delay(period);
		screenManager.updateScreen();
		while(SDL_PollEvent(&e)) 
		{
			switch(e.type)
			{
				case SDL_QUIT:
					running = false;
					w->close();
					break;
				default:
					screenManager.handleKeyStroke();
			}
		}
	}
	delete w;
	return 0;
}

