#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <map>
#include "../jsoncpp/json/json.h"
#include "Logger.h"


class Parser {
  Logger logger;
  Json::Value	config;
  std::vector<std::map<std::string, std::string>> stages;
  std::map<std::string, std::vector<std::string>> fondos_por_defecto;

  public:
    Parser(Logger logger);
    virtual ~Parser();
    int obtenerJson(std::string nombre_archivo);
    std::string obtenerNivelLog();
    std::map<std::string, std::string> obtenerEnemigos();
    std::map<std::string, std::vector<std::string>> obtenerFondos();
    std::vector<std::map<std::string, std::string>> obtenerJugadores();

  private:
    Json::Value obtenerJsonPorDefecto();
    void verificarJson();
    
};

#endif // PARSER_H