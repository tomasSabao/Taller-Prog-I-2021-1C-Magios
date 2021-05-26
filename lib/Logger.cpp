#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <new>
#include <ctime>
#include <cstdlib>
#include <chrono>

#include "Logger.h"

#define LOG_DIR "log/"
#define MAX_BUFFER_TIMESTAMP 50

using namespace std;
using chrono::system_clock;
using chrono::duration_cast;
using chrono::milliseconds;

map<string, int> nivel_log_map { {"error", 1}, {"info", 2}, {"debug", 3} };

Logger logger = Logger();

Logger::Logger()
{
    time_t tiempo_unix = time(0);
    tm * tiempo_local = localtime(&tiempo_unix);

    strftime(this->nombre_archivo, LONGITUD_NOMBRE_ARCHIVO, "%Y-%m-%d-%H%M%S.log", tiempo_local);

    string nivel = "info";
    this->path = LOG_DIR + string(this->nombre_archivo);

    imprimirSeparador("Donkey Kong II - Inicio");
}

Logger::~Logger()
{
}

int Logger::log(const string nivel, const string mensaje)
{
    nivel_log = (nivel_log.empty()) ? "error" : nivel_log;

    // si es un nivel de log valido...
    if (nivel_log_map.find(nivel) != nivel_log_map.end())
    {

        if (nivel_log_map[nivel] <= nivel_log_map[nivel_log])
        {
            ofstream f(path, ios::app);

            if (f.is_open())
            {
                auto tiempo = system_clock::now();
                auto tiempo_ms_epoch = duration_cast<milliseconds>(tiempo.time_since_epoch()).count();

                auto tiempo_ms = tiempo_ms_epoch % 1000;

                time_t tiempo_unix = system_clock::to_time_t(tiempo);
                tm * tiempo_local = localtime(&tiempo_unix);

                char timestamp[MAX_BUFFER_TIMESTAMP];
                strftime(timestamp, MAX_BUFFER_TIMESTAMP, "%Y-%m-%d %H:%M:%S", tiempo_local);

                auto timestamp_ms = timestamp;
                sprintf(timestamp_ms, "%s.%03d",timestamp,(int)tiempo_ms);

                f << timestamp << " [" << nivel << "]: " << mensaje << endl;
            }
            else
            {
                //TODO: Quitar mensajes hardcodeados
                cerr << "Error de apertura del archivo." << endl;
                return EXIT_FAILURE;
            }

        }

    }

    return EXIT_SUCCESS;
}

int Logger::guardar()
{
    return 0;
}

void Logger::imprimirSeparador(const string mensaje)
{
    log("info", "*********** DONKEY KONG II - INICIO ***********");
}

void Logger::setNivelLog(std::string nivel_log)
{
    this->nivel_log = nivel_log;
}
