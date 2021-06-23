#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>

#define LONGITUD_NOMBRE_ARCHIVO 40

using namespace std;

class Logger
{

public:
    Logger();
    virtual ~Logger();
    int log(string nivel, string mensaje);
    void setNivelLog(std::string nivel_log);

private:
    std::string nivel_log;
    int guardar();
    void imprimirSeparador(const string mensaje);
    char nombre_archivo[LONGITUD_NOMBRE_ARCHIVO];
    std::string path;
};

#endif //LOGGER_H
