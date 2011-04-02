#include <string>

#pragma once

class Logger
{
private:
	static bool loggerCreated;
	static Logger* instance;
	Logger(const char* ruta);
	Logger(const char* ruta, const char* mensajeWarning, const char* mensajeError);
	~Logger(void);
	FILE* archivoFisico;
	char* buffer;
	const char* mensajeWarning;
	const char* mensajeError;
	void escribirEnArchivo(const char* mensaje);
	
public:
	static Logger* getInstance(void);
	static void closeLog(void);
	void logWarning(const char* mensaje);
	void logError(const char* mensaje);
	FILE* obetenerArchivo(void);

};
