#include "SocketServidor.h"


SocketServidor::SocketServidor(int puerto)
{
    Comando m;
    this->comando = m;
    this->server_socket = 0;
    this->puerto = puerto;
    //this->comando=0;
    printf("Arguments: 1) port: %d \n", this->puerto);
  //  this->crearSocket();
}

SocketServidor::~SocketServidor()
{
    //dtor
}

int SocketServidor::crearSocket()
{
    printf("entre a crear socket\n");
    // Create Socket
    // int socket(int domain, int type, int protocol);
    // Domain: AF_INET (IPv4 Internet protocols)
    // Type: SOCK_STREAM (Provides  sequenced,  reliable, two-way connection-based byte streams.)
    // Protocol: 0 (chosen automatically)
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_socket == -1)
    {
        perror("Could not create socket");
        return 1;
    }
    printf("Socket created\n");
    return 0;
    //------------------------
}

int SocketServidor::getSocket()
{
    return this->server_socket;
}

int SocketServidor::bindSocket()
{

    // Prepare the sockaddr_in structure
    /* Structures for handling internet addresses
    struct sockaddr_in {
        short            sin_family;   // e.g. AF_INET
        unsigned short   sin_port;     // e.g. htons(3490)
        struct in_addr   sin_addr;     // see struct in_addr, below
        char             sin_zero[8];  // zero this if you want to
    };
    struct in_addr {
        unsigned long s_addr;  // load with inet_aton()
    }; */
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_addr.s_addr = INADDR_ANY;   //Address to accept any incoming messages. INADDR_ANY accepts any.
    this->server_addr.sin_port = htons(this->puerto); // The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
    //------------------------
    // Bind
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    // sockfd -> file descriptor that refers to a socket
    // addr -> pointer to sockaddr_in structure of the SERVER
    // addrlen -> size of the sockaddr_in structure
    // bind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd.
    if (bind(this->server_socket, (struct sockaddr *)&this->server_addr, sizeof(this->server_addr)) < 0)
    {
        perror("Bind failed. Error");
        return 1;
    }
    printf("Bind done\n");
    //------------------------
    return 0;
}
int SocketServidor::escuchar()
{

    // Listen
    // int listen(int sockfd, int backlog);
    // sockfd -> file descriptor that refers to a socket,in this case of type SOCK_STREAM
    // backlog-> The backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow.
    // listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests using accept();
    if (listen(this->server_socket, 3) < 0)
    {
        perror("Listen failed. Error");
        return 1;
    }
    printf("Listening on port: %d Waiting for incoming connections...\n", this->puerto);
    return 0;
}

int SocketServidor::aceptandoConexiones()
{
    struct sockaddr_in client_addr;
    int client_addrlen;
    //------------------------

    // Accept incoming connection from a client
    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    // sockfd -> socket that has been created with socket(), bound to a local address with bind(), and is listening for connections after a listen()
    // addr -> pointer to a sockaddr structure for the CLIENT.
    // addrlen -> size of sockaddr structure for the CLIENT.
    printf("escuchando si entra algun cliente ..., es bloqueante el accept ");
    this->client_socket = accept(this->server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);


    if (this->client_socket < 0)
    {
        perror("Accept failed");
        return 1;
    }
    printf("Connection accepted el clienteeeeeeeee numerooooo %d \n\n",this->client_socket);
    return this->client_socket;
}

int SocketServidor::getClientSocket()
{
    return this->client_socket;
}

Comando *SocketServidor::getClientComand()
{
    return this->comandoPuntero;
}


int SocketServidor::enviarDataGeneralComando(int client_socket, Comando* comando)
{
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

    while ((send_data_size > total_bytes_written) && client_socket_still_open)
    {
        printf("el servidor envia si el socket cliente  (%d ) cuando este conectado   \n", client_socket);
        bytes_written = send(client_socket, (comando+ total_bytes_written), (send_data_size - total_bytes_written), MSG_NOSIGNAL);
        if (bytes_written < 0)
        { // Error
            return bytes_written;
        }
        else if (bytes_written == 0)
        { // Socket closed
            client_socket_still_open = false;
        }
        else
        {
            total_bytes_written += bytes_written;
        }
    }

      if(total_bytes_written==send_data_size)
    {
      printf(" comando enviado al cliente  \n");

     return true;
    }else
    {
     return false;

    }
}

int SocketServidor::enviarDataGeneral(int client_socket, Modelito *modelito)
{

    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(Modelito);
    bool client_socket_still_open = true;

    // Send
    // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
    // sockfd -> file descriptor that refers to a socket
    // buf ->  the message is found in buf.
    // len -> the message and has length len
    // flags
    // The system call send() is used to transmit a message to another socket.
    // The send() call may be used only when the socket is in a connected state (so that the intended recipient is known).

    while ((send_data_size > total_bytes_written) && client_socket_still_open)
    {
        printf("el servidor envia si el socket cliente  (%d ) cuando este conectado   \n", client_socket);
        bytes_written = send(client_socket, (modelito + total_bytes_written), (send_data_size - total_bytes_written), MSG_NOSIGNAL);
        if (bytes_written < 0)
        { // Error
            return bytes_written;
        }
        else if (bytes_written == 0)
        { // Socket closed
            client_socket_still_open = false;
        }
        else
        {
            total_bytes_written += bytes_written;
        }
    }

      if(total_bytes_written==send_data_size)
    {
      printf(" modelo enviado al cliente  \n");

     return true;
    }else
    {
     return false;

    }
}

int SocketServidor::cerrar()
{
    close(this->server_socket);
    return 0;
}

/**/

int SocketServidor::recibirDataGeneral(int client_socket)
{
    Comando comandito;
    //comandito.action=0;

    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(struct Comando);
    bool client_socket_still_open = true;


    printf("numero del socket cliente que recibo= (%d ) \n", client_socket);

    while ((receive_data_size > bytes_receive) && client_socket_still_open)
    {
          printf("esperandno hata recibir unmensaje desde el socket cliente ");
        bytes_receive = recv(client_socket, (&comandito + total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);
        printf("error de recibir dato de cliente si es menor a cero = (%d ) \n", bytes_receive);
        //printf("que numero de comando recibe del cliente= (%d ) \n",  this->comando->action);
        printf("size recibe= (%d ) \n", receive_data_size);
        if (bytes_receive < 0)
        { // Error
            return bytes_receive;
        }
        else if (bytes_receive == 0)
        { // Socket closed
            client_socket_still_open = false;
        }
        else
        {
            total_bytes_receive += bytes_receive;
        }
    }


    if(total_bytes_receive==receive_data_size)
    {
     printf(" data recibido del cliente es completo, entonces guardar en el coladecomando \n");
        this->comandoPuntero=&comandito;  //this->cargarComandosSocket(comandito)  ;
     return true;
    }else
    {
     return false;

    }




}
