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
	printResult("testLogWarningConstructorSoloRuta", testLogWarningConstructorSoloRuta());
	printResult("testLogErrorConstructorSoloRuta", testLogErrorConstructorSoloRuta());
	
	//dump memory leaks to VS Output Window
	int leaks = _CrtDumpMemoryLeaks();
	printLeaks(leaks);
}

bool LoggerTests::testLogWarning(void)
{
	bool successCondition1 = false;

	const char* ruta = "log.txt";
	const char* mensaje;
	const char* mensajeWarning = "\nWarning: \0";
	const char* mensajeError = "\nError: \0";
	
	// Nuevo logger
	Logger loggerInstance(ruta, mensajeWarning, mensajeError);
	
	// Obtengo el tamanio inicial del archivo
	fseek (loggerInstance.obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoAntes = ftell(loggerInstance.obetenerArchivo());
	
	mensaje = "el escenario no tiene un nombre asignado.\0";

	// Loggeo el warning
	loggerInstance.logWarning(mensaje);

	// Obtengo el tamanio despues de loggear
	fseek (loggerInstance.obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoDespues = ftell(loggerInstance.obetenerArchivo());
	
	// Comparo el tamanio esperado con el actual
	size_t tamanioEsperado = tamanioArchivoAntes + strlen(mensaje) + strlen(mensajeWarning) + 1;
	if (tamanioEsperado == tamanioArchivoDespues) successCondition1 = true;

	// Destruyo el logger
	loggerInstance.~Logger();

	return successCondition1;

}


bool LoggerTests::testLogWarningConstructorSoloRuta(void)
{
	bool successCondition1 = false;

	const char* ruta = "log.txt";
	const char* mensaje;
	
	// Nuevo logger
	Logger loggerInstance(ruta);
	
	// Obtengo el tamanio inicial del archivo
	fseek (loggerInstance.obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoAntes = ftell(loggerInstance.obetenerArchivo());
	
	mensaje = "el la cantidad de obstaculos es superior a la esperada.\0";

	// Loggeo el warning
	loggerInstance.logWarning(mensaje);

	// Obtengo el tamanio despues de loggear
	fseek (loggerInstance.obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoDespues = ftell(loggerInstance.obetenerArchivo());
	
	// Comparo el tamanio esperado con el actual
	if (tamanioArchivoDespues > tamanioArchivoAntes) successCondition1 = true;

	// Destruyo el logger
	loggerInstance.~Logger();

	return successCondition1;

}


bool LoggerTests::testLogError(void)
{
	bool successCondition1 = false;

	const char* ruta = "log.txt";
	const char* mensaje;
	const char* mensajeWarning = "\nWarning: \0";
	const char* mensajeError = "\nError: \0";
	
	// Nuevo logger
	Logger loggerInstance(ruta, mensajeWarning, mensajeError);
	
	// Obtengo el tamanio inicial del archivo
	fseek (loggerInstance.obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoAntes = ftell(loggerInstance.obetenerArchivo());
	
	mensaje = "el tipo del obstaculo no existe.\0";

	// Loggeo el ERROR
	loggerInstance.logError(mensaje);

	// Obtengo el tamanio despues de loggear
	fseek (loggerInstance.obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoDespues = ftell(loggerInstance.obetenerArchivo());
	
	// Comparo el tamanio esperado con el actual
	size_t tamanioEsperado = tamanioArchivoAntes + strlen(mensaje) + strlen(mensajeError) + 1;
	if (tamanioEsperado == tamanioArchivoDespues) successCondition1 = true;

	// Destruyo el logger
	loggerInstance.~Logger();

	return successCondition1;

}


bool LoggerTests::testLogErrorConstructorSoloRuta(void)
{
	bool successCondition1 = false;

	const char* ruta = "log.txt";
	const char* mensaje;
	
	// Nuevo logger
	Logger loggerInstance(ruta);
	
	// Obtengo el tamanio inicial del archivo
	fseek (loggerInstance.obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoAntes = ftell(loggerInstance.obetenerArchivo());
	
	mensaje = "Linea 30 -> El tamaño de la grilla es superior al posible.\0";

	// Loggeo el warning
	loggerInstance.logError(mensaje);

	// Obtengo el tamanio despues de loggear
	fseek (loggerInstance.obetenerArchivo(), 0, SEEK_END);
	size_t tamanioArchivoDespues = ftell(loggerInstance.obetenerArchivo());
	
	// Comparo el tamanio esperado con el actual
	if (tamanioArchivoDespues > tamanioArchivoAntes) successCondition1 = true;

	// Destruyo el logger
	loggerInstance.~Logger();

	return successCondition1;

}
