#pragma once
#include <string>
#include "Image.h"
#include "Pacman.h"
#include "Window.h"
#include <string>

class ScreenManager
{
	Window* window;
	Image* fondo;
	Pacman* pacman1;
	Pacman* pacman2;
	Uint32 initialTime;
public:
	ScreenManager(Window* w, std::string pathFondo);
	void handleKeyStroke(void);
	void updateScreen(void);
	~ScreenManager(void);
};
