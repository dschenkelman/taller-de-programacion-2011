#include "StdAfx.h"
#include "Logger.h"


Logger::Logger(const char* ruta, const char* mensajeWarning, const char* mensajeError)
{
	// Abro el archivo y lo dejo listo para escribir
	this->archivoFisico = fopen(ruta, "a+");
	this->mensajeWarning = mensajeWarning;
	this->mensajeError = mensajeError;
}


Logger::~Logger()
{
	// Cierro el archivo
	int exito = fclose(this->archivoFisico);
}


void Logger::escribirEnArchivo(const char* mensaje)
{
	fwrite(mensaje, sizeof(char), strlen(mensaje), this->archivoFisico);
}


void Logger::logWarning(const char* mensaje)
{
	//TODO: Refactorizar este metodo y el de Error para no repetir tanto codigo.
	this->buffer = (char*)malloc(strlen(mensajeWarning)+strlen(mensaje)+1);
	this->buffer[0] = '\0';
	strcat(this->buffer, mensajeWarning);
	strcat(this->buffer, mensaje);
	escribirEnArchivo(this->buffer);
	free(buffer);
}


void Logger::logError(const char* mensaje)
{
	this->buffer = (char*)malloc(strlen(mensajeWarning)+strlen(mensaje)+1);
	this->buffer[0] = '\0';
	strcat(this->buffer, mensajeError);
	strcat(this->buffer, mensaje);
	escribirEnArchivo(this->buffer);
	free(buffer);
}

FILE* Logger::obetenerArchivo()
{
	return this->archivoFisico;
}