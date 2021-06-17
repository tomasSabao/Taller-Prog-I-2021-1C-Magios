#include "Conexion.h"

Conexion::Conexion()
{
    this->estado=DESCONECTADO;//no activo por defecto porque todavia no paso el login
}

Conexion::~Conexion()
{
    //dtor
}


void Conexion::setearSocket(int socket)
{
    this->socket=socket;
}

void Conexion::setearEstado(status_t estado)
{
    this->estado=estado;
}

status_t Conexion::getEstado( )
{
    return this->estado ;
}

  int  Conexion::getSocket( )
  {
   return this->socket;

  }
