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
	static bool loggerCreated;
	static Logger* instance;
public:
	Logger(const char* ruta);
	Logger(const char* ruta, const char* mensajeWarning, const char* mensajeError);
	~Logger(void);
	void logWarning(const char* mensaje);
	void logError(const char* mensaje);
	FILE* obetenerArchivo();
	Logger* Logger::getInstance() {
		if (!Logger::loggerCreated) {
			Logger* new_inst = new Logger("default_log_uri");
			Logger::instance = new_inst;
		}
		return Logger::instance;
	}
	static void closeLog() {
		delete Logger::instance;
		Logger::loggerCreated = false;
	}
};
