#include "StdAfx.h"
#include "Logger.h"
#include "LoggerTests.h"
#include <iostream>
#include <exception>
//useful to detect memory leaks
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

LoggerTests::LoggerTests(void)
{
}
LoggerTests::~LoggerTests(void)
{
}

void LoggerTests::printLeaks(int leaks)
{
	std::cout << "Logger Tests: Hubo " << leaks << " memory leaks." << endl << endl;
}

void LoggerTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void LoggerTests::run()
{
	printResult("testLogWarning", testLogWarning());
	printResult("testLogError", testLogError());
	
	//dump memory leaks to VS Output Window
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}


bool LoggerTests::testLogWarning(void)
{
	bool successCondition1 = false;

	const char* ruta = "log.txt";
	const char* mensaje;
	
	// Nuevo logger
	Logger* loggerInstance = Logger::getInstance();
	
	// Obtengo el tamanio inicial del archivo
	fseek (loggerInstance->obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoAntes = ftell(Logger::getInstance()->obetenerArchivo());
	
	mensaje = "La cantidad de obstaculos es superior a la esperada.";

	// Loggeo el warning
	loggerInstance->logWarning(mensaje);

	// Obtengo el tamanio despues de loggear
	fseek (loggerInstance->obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoDespues = ftell(Logger::getInstance()->obetenerArchivo());
	
	// Comparo el tamanio esperado con el actual
	if (tamanioArchivoDespues > tamanioArchivoAntes) successCondition1 = true;

	// Destruyo el logger
	loggerInstance->closeLog();

	return successCondition1;

}


bool LoggerTests::testLogError(void)
{
	bool successCondition1 = false;

	const char* ruta = "log.txt";
	const char* mensaje;
	
	// Nuevo logger
	Logger* logger = Logger::getInstance();
	
	// Obtengo el tamanio inicial del archivo
	fseek (logger->obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoAntes = ftell(logger->obetenerArchivo());
	
	mensaje = "Linea 30 -> El tamaño de la grilla es superior al posible.";

	// Loggeo el warning
	logger->logError(mensaje);

	// Obtengo el tamanio despues de loggear
	fseek (logger->obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoDespues = ftell(logger->obetenerArchivo());
	
	// Comparo el tamanio esperado con el actual
	if (tamanioArchivoDespues > tamanioArchivoAntes) successCondition1 = true;

	// Destruyo el logger
	logger->closeLog();

	return successCondition1;

}
