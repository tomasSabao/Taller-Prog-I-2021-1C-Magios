#include "Conexion.h"

Conexion::Conexion()
{
    //ctor
}

Conexion::~Conexion()
{
    //dtor
}


void Conexion::setearConexion(int socket)
{
    this->conexion=socket;
}

void Conexion::setearEstado(bool estado)
{
    this->estado=estado;
}

void Conexion::setearId(int id)
{
    this->id=id;
}


int Conexion::getConexion( )
{
    return this->conexion ;
}

bool Conexion::getEstado( )
{
    return this->estado ;
}

int  Conexion::getId( )
{
    return this->id;
}
