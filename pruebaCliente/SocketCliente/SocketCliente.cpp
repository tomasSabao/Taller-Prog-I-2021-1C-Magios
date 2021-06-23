#include "SocketCliente.h"


SocketCliente::SocketCliente(char* host, int puerto)
{
    //Command m;
//    this->comando=&m;
    this->skt=0;
    this->puerto=puerto;
    this->host=host;
    //this->comando=0;
    printf("Arguments: 2) host: %s, port: %d\n", this->host, this->puerto);
}

SocketCliente::~SocketCliente()
{
    //dtor
}




int SocketCliente::crearSocket()
{
    printf("entre a crear socket\n");
    // Create Socket
    // int socket(int domain, int type, int protocol);
    // Domain: AF_INET (IPv4 Internet protocols)
    // Type: SOCK_STREAM (Provides  sequenced,  reliable, two-way connection-based byte streams.)
    // Protocol: 0 (chosen automatically)
    this->skt = socket(AF_INET , SOCK_STREAM , 0);
    if (this->skt == -1)
    {
        perror("Could not create socket");
        return 1;
    }
    printf("Socket created\n");
    //------------------------
    return 0;
}

int SocketCliente::conectar()
{
    // Prepare the sockaddr_in structure
    this->server_addr.sin_addr.s_addr = inet_addr((const char*)this->host);
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(this->puerto);

    //Connect to remote server
    // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    // sockfd -> file descriptor that refers to a socket
    // addr -> pointer to sockaddr_in structure for the SERVER.
    // addrlen -> size of sockaddr_in structure for the SERVER.
    // The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr.
    if (connect(this->skt, (struct sockaddr *)&this->server_addr, sizeof(struct sockaddr_in)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
    printf("Connected\n\n");
    return 0;
}

int SocketCliente::enviarData(Comando* comando)
{
    Modelo model;
    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(Comando);
    bool client_socket_still_open = true;

    // Send
    // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
    // sockfd -> file descriptor that refers to a socket
    // buf ->  the message is found in buf.
    // len -> the message and has length len
    // flags
    // The system call send() is used to transmit a message to another socket.
    // The send() call may be used only when the socket is in a connected state (so that the intended recipient is known).

    while ((send_data_size > total_bytes_written) && client_socket_still_open) {
        printf("el socket cliente (%d) envia\n",this->skt);
        bytes_written = send(this->skt, (comando + total_bytes_written), (send_data_size - total_bytes_written), MSG_NOSIGNAL);
        if (bytes_written < 0) { // Error
            return bytes_written;
        }
        else if (bytes_written == 0) { // Socket closed
            client_socket_still_open = false;
        }
        else {
            total_bytes_written += bytes_written;
        }
    }

    if(total_bytes_written==send_data_size)
    {
            printf(" data  enviado al servidor \n");
         //this->modelo=&model;
         return true;
    }else
    {
     return false;
    }
}

int SocketCliente::cerrar()
{
 close(this->skt);
 return 0;
}

int SocketCliente::recibirDataComando()
{
    Comando unComando;

    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(Comando);
    bool client_socket_still_open = true;


    // The recv() call are used to receive messages from a socket.
    // If no messages are available at the socket, the receive call wait for a message to arrive. (Blocking)
     printf("numero del socket cliente que recibo= (%d ) \n",  this->skt);

    while ((receive_data_size > bytes_receive) && client_socket_still_open) {
        printf("recibe el cliente = (%d ) \n", this->skt);
        bytes_receive = recv(this->skt, (&unComando + total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);
        printf("error de recibir dato de cliente si es menor a cero = (%d ) \n",bytes_receive);
        //printf("que numero de comando recibe del cliente= (%d ) \n",  this->comando->action);
        printf("size recibe= (%d ) \n", receive_data_size);
        if (bytes_receive < 0) { // Error
            printf("hubo un error en recibirData cliente socket");
            return bytes_receive;
        }
        else if (bytes_receive == 0) { // Socket closed
            printf("Se cerro el socket en recibirData cliente socket");
            client_socket_still_open = false;
        }
        else {
            total_bytes_receive += bytes_receive;
        }
    }

    if(total_bytes_receive==bytes_receive)
    {
            printf(" data recibido del cliente es completo, entonces guardar en el coladecomando \n");
         this->unComando=&unComando;
         return true;
    }else
    {
     return false;
    }



}


int SocketCliente::recibirData()
{
    Modelo model;

    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(Modelo);
    bool client_socket_still_open = true;


    // The recv() call are used to receive messages from a socket.
    // If no messages are available at the socket, the receive call wait for a message to arrive. (Blocking)
     printf("numero del socket cliente que recibo= (%d ) \n",  this->skt);

    while ((receive_data_size > bytes_receive) && client_socket_still_open) {
        printf("recibe el cliente = (%d ) \n", this->skt);
        bytes_receive = recv(this->skt, (&model + total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);
        printf("error de recibir dato de cliente si es menor a cero = (%d ) \n",bytes_receive);
        //printf("que numero de comando recibe del cliente= (%d ) \n",  this->comando->action);
        printf("size recibe= (%d ) \n", receive_data_size);
        if (bytes_receive < 0) { // Error
            printf("hubo un error en recibirData cliente socket");
            return bytes_receive;
        }
        else if (bytes_receive == 0) { // Socket closed
            printf("Se cerro el socket en recibirData cliente socket");
            client_socket_still_open = false;
        }
        else {
            total_bytes_receive += bytes_receive;
        }
    }

    if(total_bytes_receive==bytes_receive)
    {
            printf(" data recibido del cliente es completo, entonces guardar en el coladecomando \n");
         this->modelo=&model;
         return true;
    }else
    {
     return false;
    }



}

Modelo* SocketCliente::getServerModel() {
    return this->modelo;
}

Comando* SocketCliente::getServerComando() {
    return this->unComando;
}
