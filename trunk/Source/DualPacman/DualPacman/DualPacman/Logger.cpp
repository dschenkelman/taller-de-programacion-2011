#include "StdAfx.h"
#include "Logger.h"
#include <time.h>

bool Logger::loggerCreated = false;
Logger* Logger::instance = NULL;

Logger::Logger(const char* ruta)
{
	// Abro el archivo y lo dejo listo para escribir
	fopen_s(&this->archivoFisico, ruta, "a+");
	this->mensajeWarning = "  Warning: \0";
	this->mensajeError = "  Error: \0";
}


Logger::Logger(const char* ruta, const char* mensajeWarning, const char* mensajeError)
{
	// Abro el archivo y lo dejo listo para escribir
	fopen_s(&this->archivoFisico, ruta, "a+");
	this->mensajeWarning = mensajeWarning;
	this->mensajeError = mensajeError;
}

Logger::~Logger()
{
	// Cierro el archivo
	if (this->archivoFisico != NULL)
		int exito = fclose(this->archivoFisico);
}


Logger* Logger::getInstance(void) {
	if (!loggerCreated)
	{
		instance = new Logger("parser.log.txt");
		loggerCreated = true;
	}
	return instance;
}


void Logger::closeLog(void) {
	delete instance;
	instance = NULL;
	loggerCreated = false;
}


void Logger::escribirEnArchivo(const char* mensaje)
{
	time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
	fwrite(output, sizeof(char), strlen(output), this->archivoFisico);
	fwrite(mensaje, sizeof(char), strlen(mensaje), this->archivoFisico);
}


void Logger::logWarning(std::string msg)
{
	msg += '\n';
	const char* mensaje = msg.c_str();
	this->buffer = (char*)malloc(strlen(mensajeWarning)+strlen(mensaje)+1);
	this->buffer[0] = '\0';
	strcat_s(this->buffer, strlen(mensajeWarning)+strlen(mensaje)+1,this->mensajeWarning);
	strcat_s(this->buffer, strlen(mensajeWarning)+strlen(mensaje)+1, mensaje);
	escribirEnArchivo(this->buffer);
	free(buffer);
}


void Logger::logError(std::string msg)
{
	msg += '\n';
	const char* mensaje = msg.c_str();
	this->buffer = (char*)malloc(strlen(this->mensajeError)+strlen(mensaje)+1);
	this->buffer[0] = '\0';
	strcat_s(this->buffer, strlen(this->mensajeError)+strlen(mensaje)+1,this->mensajeError);
	strcat_s(this->buffer, strlen(this->mensajeError)+strlen(mensaje)+1, mensaje);
	escribirEnArchivo(this->buffer);
	free(buffer);
}


FILE* Logger::obetenerArchivo()
{
	return this->archivoFisico;
}

size_t Logger::obtenerTamanioArchivo(void)
{
	fseek (this->archivoFisico, 0, SEEK_END);
	return ftell(this->archivoFisico);
}