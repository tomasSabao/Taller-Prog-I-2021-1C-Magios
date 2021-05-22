#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <sstream>
#include "../jsoncpp/json/json.h"

#include "Parser.h"
#include "Logger.h"

#define ENEMIGOS_CANTIDAD_DEFAULT 10
#define ENEMIGOS_CANTIDAD_MINIMA 0
#define ENEMIGOS_CANTIDAD_MAXIMA 30

#define PATH_FONDO1 "fondo.png"
#define PATH_FONDO2 "fondo2.png"

using namespace std;


Parser::Parser(Logger logger) {
  this->logger = logger;
}

Parser::~Parser() {
}

Json::Value Parser::obtenerJsonPorDefecto() {
  Json::Value config;
  Json::Reader lector;

  cout << "Por defecto se abre el archivo de configuracion por default" << endl;
  this->logger.log("info","Se abre archivo de configuracion por default");

  ifstream archivo("lib/default.json", ios::in);

  // Parsear JSON
  lector.parse(archivo, config);

  archivo.close();
  return config;
}

void Parser::verificarJson() {
  if (!this->config.isMember("configuration")) {
    this->logger.log("info","No se encontro el campo configuration en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
  }
  if (!this->config["configuration"].isMember("log")) {
    this->logger.log("info","No se encontro el campo configuration->log en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
  }
  if (!this->config["configuration"]["log"].isMember("level")) {
    this->logger.log("info","No se encontro el campo configuration->log->level en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
  }
  if (!this->config["configuration"].isMember("game")) {
    this->logger.log("info","No se encontro el campo configuration->game en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
  }
  if (!this->config["configuration"]["game"].isMember("enemies")) {
    this->logger.log("info","No se encontro el campo configuration->game->enemies en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
  }

  if (!this->config["configuration"]["game"].isMember("stages")) {
    this->logger.log("info","No se encontro el campo configuration->game->stages en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
  }

  //TODO: emprolijar esto
  if ((this->config["configuration"]["log"]["level"].asString() == "ERROR") ||
      (this->config["configuration"]["log"]["level"].asString() == "DEBUG") ||
      (this->config["configuration"]["log"]["level"].asString() == "INFO")) {
  } else {
    this->logger.log("info","Nivel de log invalido");
    this->logger.log("info","Se configura por default INFO como nivel de log");
    this->config["configuration"]["log"]["level"] = "INFO";
  }
  for (int i = 0; i < this->config["configuration"]["game"]["enemies"].size(); i++ ) {
    if ((stoi(this->config["configuration"]["game"]["enemies"][i]["quantity"].asString()) < ENEMIGOS_CANTIDAD_MINIMA) ||
        (stoi(this->config["configuration"]["game"]["enemies"][i]["quantity"].asString()) > ENEMIGOS_CANTIDAD_MAXIMA)) {

      this->logger.log("info","Cantidad de enemigos invalida");
      this->logger.log("info","Se configura por default 10 como la cantidad de enemigos");
      this->config["configuration"]["game"]["enemies"][i]["quantity"] = ENEMIGOS_CANTIDAD_DEFAULT;
    }
  }

    //TODO: chequeo que exista el file del fondo.
    string nombre_archivo1 = this->config["configuration"]["game"]["stages"]["fondo1"].asString();
    string nombre_archivo2 = this->config["configuration"]["game"]["stages"]["fondo2"].asString();

    ifstream archivo1(nombre_archivo1.c_str());
    ifstream archivo2(nombre_archivo2.c_str());

    if (!archivo1.good()) {
        this->config["configuration"]["game"]["stages"]["fondo1"] = PATH_FONDO1;
        this->logger.log("info","Archivo de fondo invalido");
        this->logger.log("info","Se configura por default otro fondo");
    }
    if (!archivo2.good()) {
        this->config["configuration"]["game"]["stages"]["fondo1"] = PATH_FONDO1;
        this->logger.log("info","Archivo de fondo invalido");
        this->logger.log("info","Se configura por default otro fondo");
    }
}

int Parser::obtenerJson(string nombre_archivo) {
  Json::Value config;

  this->logger.log("info","Se abre archivo de configuracion");
  if (nombre_archivo.find(".json") == string::npos) {
    cout << "Archivo con formato distinto a un .json" << endl;
    this->logger.log("info","No se encontro el archivo .json de configuracion");
    this->config = obtenerJsonPorDefecto();
  }
  Json::Reader lector;

  ifstream archivo(nombre_archivo, ios::in);
  if (archivo) {
    if (!lector.parse(archivo, this->config)) {
      this->logger.log("info", lector.getFormattedErrorMessages());
      cerr << lector.getFormattedErrorMessages() << endl;
      archivo.close();
      this->config = obtenerJsonPorDefecto();
    } else {
      archivo.close();
    }
  }

  verificarJson();
  return 0;
}

map<string, string> Parser::obtenerEnemigos() {
  map<string, string> aux;
  for (int i = 0; i < this->config["configuration"]["game"]["enemies"].size(); i++) {
    string tipo = this->config["configuration"]["game"]["enemies"][i]["type"].asString();
    string val = this->config["configuration"]["game"]["enemies"][i]["quantity"].asString();
    aux[tipo] = val;
  }

  return aux;
}

vector<string> Parser::obtenerFondos() {
  vector<string> aux;

  aux.push_back(this->config["configuration"]["game"]["stages"]["fondo1"].asString());
  aux.push_back(this->config["configuration"]["game"]["stages"]["fondo2"].asString());

  return aux;
}

string Parser::obtenerNivelLog() {
  string aux = this->config["configuration"]["log"]["level"].asString();
  return aux;
}

vector<map<string, string>> Parser::obtenerJugadores() {
  vector<map<string, string>> aux(this->config["configuration"]["players"].asInt());

  //TODO: arreglar esto TP2
  for(int i = 0; i < this->config["configuration"]["players"].asInt(); i++) {
    aux[i]["username"] = this->config["configuration"]["users"]["username"][i].asString();
    aux[i]["password"] = this->config["configuration"]["users"]["password"][i].asString();
  }

  return aux;
}
