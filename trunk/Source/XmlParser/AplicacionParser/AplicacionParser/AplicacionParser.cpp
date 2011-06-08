// AplicacionParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "vld.h"
#include "ListTests.h"
#include "ScreenManager.h"
#include "XmlParser.h"
#include "Image.h"
#include "Window.h"
#include <iostream>
#include "time.h"
#include "PresentationActivity.h"
#include "ParameterHolder.h"
using namespace std;

//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


void printLeaks(int leaks)
{
	std::cout << "MAIN: Hubo " << leaks << " memory leaks." << endl << endl;
}

int execute(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout<<"Sintaxis: ApplicationParser nombreArch.xml modoVideo (640 | 800 | 1024)"<<endl;
		return 0;
	}
	
	int videoMode =640;
	char* fileName = argv[1];
	videoMode = atoi(argv[2]);

	int width = videoMode;
	int height = ((videoMode * 3) / 4);
	Window* w = new Window("DualPacman", height, width);

	ParameterHolder* parameters = new ParameterHolder();
	parameters->addParameter("fileName",fileName);
	parameters->addIntParameter("winWidth", width);
	parameters->addIntParameter("winHeight", height);

	// Actividad de Inicio
	PresentationActivity* pActivity = new PresentationActivity(width, height);
	pActivity->init();
	
	// Seteo la actividad
	w->setCurrentActivity(pActivity);
	
	pActivity->drawViews();

	// Actualizo la ventana
	w->refresh();
	
	// Inicio manejo de eventos
	w->init();				

	delete parameters;
	delete w;
	
	return 0;
}

int main(int argc, char* argv[])
{
	int res = execute(argc, argv);
	//int leaks = _CrtDumpMemoryLeaks();
	//printLeaks(leaks);

	char aux;
	cin >> aux;
	return res;
}

//int _tmain(int argc, _TCHAR* argv[])
//{
	/*cout<<"Test de List<T>"<<endl;
	ListTests listTests;
	listTests.run();
	
	cout<<"Test de Stack<T>"<<endl;
	StackTests stackTests;
	stackTests.run();*/

	/*cout<<"Test de String"<<endl;
	StringTests stringTests;
	stringTests.run();*/

	/*cout<<"Test de Logger"<<endl;
	LoggerTests loggerTests;
	loggerTests.run();

	cout<<"Test de XmlElement"<<endl;
	XmlElementTests xmlElementTests;
	xmlElementTests.run();

	cout<<"Test de TipoObstaculo"<<endl;
	TipoObstaculoTests tipoObstaculoTests;
	tipoObstaculoTests.run();

	cout<<"Test de TipoBonus"<<endl;
	TipoBonusTests tipoBonusTests;
	tipoBonusTests.run();

	cout<<"Test de Bonus"<<endl;
	BonusTests bonusTets;
	bonusTets.run();

	cout<<"Test de Obstaculo"<<endl;
	ObstaculoTests obstaculoTests;
	obstaculoTests.run();

	cout<<"Test de Camino"<<endl;
	CaminoTests caminoTests;
	caminoTests.run();

	cout<<"Test de CellMatrix"<<endl;
	CellMatrixTests cellMatrixTests;
	cellMatrixTests.run();

	cout<<"Test de Grilla"<<endl;
	GrillaTests grillaTests;
	grillaTests.run();

	cout<<"Test de Escenario"<<endl;
	EscenarioTests escenarioTests;
	escenarioTests.run();
	*/
	/*cout<<"Test de XmlParser"<<endl;
	XmlParserTest xmlParserTest;
	xmlParserTest.run();*/

	/*cout<<"Test de Textura"<<endl;
	TexturaTests texturaTests;
	texturaTests.run();

	cout<<"Test de Image"<<endl;
	ImageTests imageTest;
	imageTest.run();*/

	

	/*Window w("Ventana", 480, 640);
	Image im("Images/smile.bmp");
	Image im2("Images/anana.bmp");
	Image im3("Images/anana.bmp");
	w.display(im, 100, 100);
	w.display(im2, 100, 300);
	w.refresh();
	im2.superImpose(im);
	
	w.display(im2, 200,50);
	w.refresh();

	im.superImpose(im3);
	w.display(im, 400,50);
	w.refresh();*/
	
	/*testLeaks();
*/
//	int leaks = _CrtDumpMemoryLeaks();
//	printLeaks(leaks);
//	char c = getchar();
//
//
//	return 0;
//}


//int _tmain(int argc, _TCHAR* argv[]){
//	
//	int videoMode =640;
//	int width = videoMode;
//	int height = ((videoMode * 3) / 4);
//	Window* w = new Window("DualPacman", height, width);
//
//	// Actividad de Inicio
//	PresentationActivity* pActivity = new PresentationActivity(width, height);
//	pActivity->init();
//	
//	// Seteo la actividad
//	w->setCurrentActivity(pActivity);
//	
//	pActivity->drawViews();
//
//	// Actualizo la ventana
//	w->refresh();
//	
//	// Inicio manejo de eventos
//	w->init();				
//
//
//	delete w;
//	
//	
//	return 0;
//}