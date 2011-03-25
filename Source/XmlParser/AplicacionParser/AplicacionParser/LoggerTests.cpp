#include "StdAfx.h"
#include "Logger.h"
#include "LoggerTests.h"
#include <iostream>

LoggerTests::LoggerTests(void)
{
}
LoggerTests::~LoggerTests(void)
{
}

void LoggerTests::printResult(std::string testName, bool result)
{
	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
}

void LoggerTests::run()
{
	std::cout << ("\n ::LoggerTests::\n");
	printResult("testLogWarning", testLogWarning());
	printResult("testLogError", testLogError());
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
	
	mensaje = "el escenario no tiene un nombre asignado.";

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
	
	mensaje = "el tipo del obstaculo no existe.";

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