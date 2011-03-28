#include <string>

#pragma once

class Logger
{
private:
	FILE* archivoFisico;
	char* buffer;
	const char* mensajeWarning;
	const char* mensajeError;
	void escribirEnArchivo(const char* mensaje);
public:
	Logger(const char* ruta);
	Logger(const char* ruta, const char* mensajeWarning, const char* mensajeError);
	~Logger(void);
	void logWarning(const char* mensaje);
	void logError(const char* mensaje);
	FILE* obetenerArchivo();
};