#include "StdAfx.h"
#include "ImageTests.h"
#include "Image.h"
#include <string>
#include <iostream>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

ImageTests::ImageTests(void)
{
}
ImageTests::~ImageTests(void)
{
}

void ImageTests::printLeaks(int leaks)
{
	std::cout << "Image Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void ImageTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void ImageTests::run()
{
	printResult("testResizeToSmaller", testResizeToSmaller());
	printResult("testResizeToBigger", testResizeToBigger());
	
	//dump memory leaks to VS Output Window
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}


bool ImageTests::testResizeToSmaller(void)
{
	bool successCondition = false;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	SDL_Surface *screen;
	 
	screen = SDL_SetVideoMode(640, 480, 24, SDL_DOUBLEBUF);
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	
	// nueva imagen
	Image* imgSmile = new Image("Images/smile.bmp");

	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = imgSmile->getWidth();
	src.h = imgSmile->getHeight();
	dest.x = 50;
	dest.y = 20;
	dest.w = imgSmile->getWidth();
	dest.h = imgSmile->getHeight();
	SDL_BlitSurface(imgSmile->getSDLSurface(), &src, screen, &dest);
	SDL_Flip(screen);
	
	// nueva imagen
	Image* imgSmileRe = new Image("Images/smile.bmp");


	// Achico la imagen
	imgSmileRe->resize(18, 18);
	
	// Pego la imagen en la pantalla
	src.x = 0;
	src.y = 0;
	src.w = imgSmileRe->getWidth();
	src.h = imgSmileRe->getHeight();
	dest.x = 100;
	dest.y = 20;
	dest.w = imgSmileRe->getWidth();
	dest.h = imgSmileRe->getHeight();
	SDL_BlitSurface(imgSmileRe->getSDLSurface(), &src, screen, &dest);
	SDL_Flip(screen);


	//esperar para cerrar
	SDL_Event e;
	bool running = true;
 
	while(running) 
	{
		while(SDL_PollEvent(&e)) 
		{
			switch(e.type)
			{
				case SDL_QUIT:
					running = false;
					SDL_Quit();
					break;
			}
		}
	}
	
	// libero memoria
	free(imgSmile);
	free(imgSmileRe);
	
	successCondition = true;
	
	return successCondition;

}



bool ImageTests::testResizeToBigger(void)
{
	bool successCondition = false;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	SDL_Surface *screen;
	 
	screen = SDL_SetVideoMode(640, 480, 24, SDL_DOUBLEBUF);
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	
	// nueva imagen
	Image* imgSmile = new Image("Images/smile.bmp");

	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = imgSmile->getWidth();
	src.h = imgSmile->getHeight();
	dest.x = 50;
	dest.y = 20;
	dest.w = imgSmile->getWidth();
	dest.h = imgSmile->getHeight();
	SDL_BlitSurface(imgSmile->getSDLSurface(), &src, screen, &dest);
	SDL_Flip(screen);
	
	// Achico la imagen
	imgSmile->resize(100, 100);
	
	// Pego la imagen en la pantalla
	src.x = 0;
	src.y = 0;
	src.w = imgSmile->getWidth();
	src.h = imgSmile->getHeight();
	dest.x = 100;
	dest.y = 20;
	dest.w = imgSmile->getWidth();
	dest.h = imgSmile->getHeight();
	SDL_BlitSurface(imgSmile->getSDLSurface(), &src, screen, &dest);
	SDL_Flip(screen);

	//esperar para cerrar
	SDL_Event e;
	bool running = true;
 
	while(running) 
	{
		while(SDL_PollEvent(&e)) 
		{
			switch(e.type)
			{
				case SDL_QUIT:
					running = false;
					SDL_Quit();
					break;
			}
		}
	}
	
	// libero memoria
	free(imgSmile);
	
	successCondition = true;
	
	return successCondition;
}