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

#define PATH_DEFAULT_FONDO1 "fondo1_default.png"
#define PATH_DEFAULT_FONDO2 "fondo2_default.png"

using namespace std;

extern Logger logger;

Parser::Parser()
{
}

Parser::~Parser()
{
}

Json::Value Parser::obtenerJsonPorDefecto()
{
  Json::Value config;
  Json::Reader lector;

  logger.log("error", "Se abre el archivo de configuracion por defecto");
  ifstream archivo("default.json", ios::in);

  // Parsear JSON
  lector.parse(archivo, config);

  archivo.close();
  return config;
}

void Parser::verificarJson()
{
  if (!this->config.isMember("configuration"))
  {
    logger.log("error", "No se encontro el campo configuration en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
    return;
  }
  if (!this->config["configuration"].isMember("log"))
  {
    logger.log("error", "No se encontro el campo configuration->log en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
    return;
  }
  if (!this->config["configuration"]["log"].isMember("level"))
  {
    logger.log("error", "No se encontro el campo configuration->log->level en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
    return;
  }
  if (!this->config["configuration"].isMember("game"))
  {
    logger.log("error", "No se encontro el campo configuration->game en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
    return;
  }
  if (!this->config["configuration"]["game"].isMember("enemies"))
  {
    logger.log("error", "No se encontro el campo configuration->game->enemies en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
    return;
  }
  if (!this->config["configuration"]["game"].isMember("stages"))
  {
    logger.log("error", "No se encontro el campo configuration->game->stages en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
    return;
  }

  if ((this->config["configuration"]["log"]["level"].asString() == "error") ||
      (this->config["configuration"]["log"]["level"].asString() == "debug") ||
      (this->config["configuration"]["log"]["level"].asString() == "info"))
  {
  }
  else
  {
    logger.log("error", "Dentro de configuration->log, el nivel de log invalido");
    logger.log("error", "Se configura por default INFO como nivel de log");

    cerr << "Nivel de log invalido" << endl;
    cout << "Se configura por default info como nivel de log" << endl;
    this->config["configuration"]["log"]["level"] = "info";
  }
  for (int i = 0; i < this->config["configuration"]["game"]["enemies"].size(); i++)
  {

    //ver que tipos de enemigos existen.
    if (this->config["configuration"]["game"]["enemies"][i]["type"].asString().compare("fuego-" + to_string(i + 1)))
    {
      logger.log("error", "Dentro de configuration->game->enemies, el tipo de enemigo de nivel " + to_string(i + 1) + " invalida");
      logger.log("error", "Se configura por default un enemigo para el nivel " + to_string(i + 1));

      cerr << "Tipo de enemigo invalido" << endl;
      cout << "Se configura por default un enemigo" << endl;
      this->config["configuration"]["game"]["enemies"][i]["type"] = "fuego-default-" + to_string(i + 1);
    }

    //chequeo de cantidades
    try
    {
      int cantidad_enemigos = stoi(this->config["configuration"]["game"]["enemies"][i]["quantity"].asString());

      if (cantidad_enemigos < ENEMIGOS_CANTIDAD_MINIMA ||
          cantidad_enemigos > ENEMIGOS_CANTIDAD_MAXIMA) {
        logger.log("error", "Dentro de configuration->game->enemies, la cantidad de enemigos de nivel " + to_string(i + 1) + " invalida");
        logger.log("error", "Se configura por default 10 como cantidad de enemigos en nivel " + to_string(i + 1));

        cerr << "Cantidad de enemigos invalida" << endl;
        cout << "Se configura por default 10 como la cantidad de enemigos" << endl;
        this->config["configuration"]["game"]["enemies"][i]["quantity"] = ENEMIGOS_CANTIDAD_DEFAULT;
      }
    }
    catch (exception &err)
    {
      logger.log("error", "Dentro de configuration->game->enemies, la cantidad de enemigos de nivel " + to_string(i + 1) + " invalida");
      logger.log("error", "Se configura por default 10 como cantidad de enemigos en nivel " + to_string(i + 1));
      cerr << "Cantidad de enemigos invalida: no es un entero" << endl;
      cout << "Se configura por default 10 como la cantidad de enemigos" << endl;
      this->config["configuration"]["game"]["enemies"][i]["quantity"] = ENEMIGOS_CANTIDAD_DEFAULT;
    }
  }

  //TODO: chequeo que exista el file del fondo.
  string nombre_archivo1 = this->config["configuration"]["game"]["stages"]["fondo1"].asString();
  string nombre_archivo2 = this->config["configuration"]["game"]["stages"]["fondo2"].asString();

  ifstream archivo1(nombre_archivo1.c_str());
  ifstream archivo2(nombre_archivo2.c_str());

  if (!archivo1.good())
  {
    this->config["configuration"]["game"]["stages"]["fondo1"] = PATH_DEFAULT_FONDO1;
    logger.log("error", "Dentro de configuration->game->stages, el archivo de fondo de nivel 1 invalido");
    logger.log("error", "Se configura por default el fondo de nivel 1");

    cerr << "Archivo de fondo de nivel 1 invalido" << endl;
    cout << "Se configura por default otro fondo para nivel 1" << endl;
  }
  if (!archivo2.good())
  {
    this->config["configuration"]["game"]["stages"]["fondo2"] = PATH_DEFAULT_FONDO2;
    logger.log("error", "Dentro de configuration->game->stages, el archivo de fondo de nivel 2 invalido");
    logger.log("error", "Se configura por default el fondo de nivel 2");

    cerr << "Archivo de fondo de nivel 2 invalido" << endl;
    cout << "Se configura por default otro fondo para nivel 2" << endl;
  }

  if (!this->config["configuration"].isMember("players"))
  {
    logger.log("error", "No se encontro el campo configuration->players en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
    return;
  }
  if (!this->config["configuration"].isMember("users"))
  {
    logger.log("error", "No se encontro el campo configuration->users en el archivo de configuracion");
    this->config = obtenerJsonPorDefecto();
    return;
  }

  try
  {
    int cantidad_jugadores = stoi(this->config["configuration"]["players"].asString());
    if (cantidad_jugadores != this->config["configuration"]["users"].size())
    {
      logger.log("error", "No hay compatibilidad entre la cantidad de jugadores ingresada y la cantidad de usuarios y contrasenias en el archivo de configuracion");
      this->config = obtenerJsonPorDefecto();
      return;
    }
  }
  catch (exception &err)
  {
    logger.log("error", "Dentro de configuration->players, la cantidad de jugadores es invalida");
    cerr << "Cantidad de jugadores invalida: no es un entero" << endl;
    this->config = obtenerJsonPorDefecto();
    return; 
  }

  cout << "Finalizan los chequeos del archivo de configuracion dado por el user" << endl;
}

int Parser::obtenerJson(string nombre_archivo)
{
  Json::Value config;

  cout << "Se trata de abrir archivo de configuracion" << endl;
  if (nombre_archivo.find(".json") == string::npos)
  {
    logger.log("error", "Tipo de archivo con distinto formato a un .json");
    cerr << "No se encontro el archivo .json de configuracion" << endl;
    this->config = obtenerJsonPorDefecto();
    return 0;
  }

  Json::Reader lector;

  logger.log("info", "Se abre archivo de configuracion");

  ifstream archivo(nombre_archivo, ios::in);
  if (archivo)
  {
    if (!lector.parse(archivo, this->config))
    {
      logger.log("error", lector.getFormattedErrorMessages());
      cerr << lector.getFormattedErrorMessages() << endl;
      archivo.close();
      this->config = obtenerJsonPorDefecto();
      return 0;
    }
    else
    {
      archivo.close();
    }
  }

  verificarJson();
  return 0;
}

map<string, string> Parser::obtenerEnemigos()
{
  map<string, string> aux;
  for (int i = 0; i < this->config["configuration"]["game"]["enemies"].size(); i++)
  {
    string tipo = this->config["configuration"]["game"]["enemies"][i]["type"].asString();
    string val = this->config["configuration"]["game"]["enemies"][i]["quantity"].asString();
    aux[tipo] = val;
  }

  return aux;
}

vector<string> Parser::obtenerFondos()
{
  vector<string> aux;

  aux.push_back(this->config["configuration"]["game"]["stages"]["fondo1"].asString());
  aux.push_back(this->config["configuration"]["game"]["stages"]["fondo2"].asString());

  return aux;
}

string Parser::obtenerNivelLog()
{
  string aux = this->config["configuration"]["log"]["level"].asString();
  return aux;
}

bool Parser::validarJugador(string user, string password)
{
  for (int i = 0; i < this->config["configuration"]["users"].size(); i++)
  {
    if ((this->config["configuration"]["users"][i]["username"].asString() == user) && (this->config["configuration"]["users"][i]["password"].asString() == password))
    {
      return true;
    }
  }
  return false;
}