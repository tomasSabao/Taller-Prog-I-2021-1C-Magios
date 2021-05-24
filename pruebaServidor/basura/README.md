# Socket - Ejemplo básico

El ejemplo se compone de dos archivos:
```
server.c
client.c
```

## Server

La aplicación SERVER recibe como único argumento el puerto en el cual recibirá peticiones de coneccion.
```
_> ./server 5555
```
## Client
La aplicación CLIENT recibe dos argumento, el primero es la ip a la cual se quiere conectar y el segundo es el puerto específico.
```
_> ./client 127.0.0.1 5555
```

## Observaciones
Este ejemplo simula un servidor que recibe comandos de otra aplicación cliente, los procesa y retorna datos al cliente.

Este ejemplo funciona de forma sincronica entre el servidor y un único cliente.