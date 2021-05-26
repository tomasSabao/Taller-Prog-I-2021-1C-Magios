#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <map>
#include "../jsoncpp/json/json.h"


class Parser {
  Json::Value config;

  public:
    Parser();
    virtual ~Parser();
    int obtenerJson(std::string nombre_archivo);
    std::string obtenerNivelLog();
    std::map<std::string, std::string> obtenerEnemigos();
    std::vector<std::string> obtenerFondos();
    std::vector<std::map<std::string, std::string>> obtenerJugadores();

  private:
    Json::Value obtenerJsonPorDefecto();
    void verificarJson();

};

#endif // PARSER_H
