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

#define MAX_BUFFER_TIMESTAMP 50

// TODO: tomar desde .json
#define LOG_LEVEL "info"

using namespace std;
using chrono::system_clock;
using chrono::duration_cast;
using chrono::milliseconds;

map<string, int> nivel_log { {"error", 1}, {"info", 2}, {"debug", 3} };

Logger::Logger()
{
    time_t tiempo_unix = time(0);
    tm * tiempo_local = localtime(&tiempo_unix);

    strftime(nombre_archivo, LONGITUD_NOMBRE_ARCHIVO, "%Y-%m-%d.log", tiempo_local);

    string nivel = "info";

    imprimirSeparador("Donkey Kong II - Inicio");
}

Logger::~Logger()
{
}

int Logger::log(const string nivel, const string mensaje)
{
    if (nivel_log.find(nivel) != nivel_log.end())
    {
        if (nivel_log[nivel] <= nivel_log[LOG_LEVEL])
        {
            ofstream f(nombre_archivo, ios::app);

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

                f << "[" << nivel << "] " << timestamp << "  - " << mensaje << endl;
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
