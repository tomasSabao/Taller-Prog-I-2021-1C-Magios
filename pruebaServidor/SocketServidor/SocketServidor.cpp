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
    this->client_socket = accept(this->server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);
    printf("este es el clienteeeeeeeee numerooooo %d ", this->client_socket);

    if (this->client_socket < 0)
    {
        perror("Accept failed");
        return 1;
    }
    printf("Connection accepted\n\n");
    return this->client_socket;
}

int SocketServidor::getClientSocket()
{
    return this->client_socket;
}

Comando *SocketServidor::getClientComand()
{
    return &this->comando;
}

int SocketServidor::enviarData(Modelo *modelo)
{

    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(Modelo);
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
        printf("el servidor envia al socket del  cliente = (%d ) \n", this->client_socket);
        bytes_written = send(this->client_socket, (modelo + total_bytes_written), (send_data_size - total_bytes_written), MSG_NOSIGNAL);
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

    return 0;
}

int SocketServidor::enviarDataGeneral(int client_socket, Modelo *modelo)
{

    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(Modelo);
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
        printf("el servidor envia al socket del  cliente = (%d ) \n", client_socket);
        bytes_written = send(client_socket, (modelo + total_bytes_written), (send_data_size - total_bytes_written), MSG_NOSIGNAL);
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

    return 0;
}

int SocketServidor::cerrar()
{
    close(this->server_socket);
    return 0;
}

int SocketServidor::recibirData()
{
    Comando comandito;

    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(struct Comando);
    bool client_socket_still_open = true;

    // Receive
    // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    // sockfd -> file descriptor that refers to a socket
    // buf -> where the received message into the buffer buf.
    // len -> The caller must specify the size of the buffer in len.
    // flags
    // The recv() call are used to receive messages from a socket.
    // If no messages are available at the socket, the receive call wait for a message to arrive. (Blocking)
    printf("numero del socket cliente que recibo= (%d ) \n", this->client_socket);

    while ((receive_data_size > bytes_receive) && client_socket_still_open)
    {
        printf("el servidor recibe del  socket del  cliente = (%d ) \n", this->client_socket);
        bytes_receive = recv(this->client_socket, (&comandito + total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);
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

    this->comando = comandito;
    return 0;
}

int SocketServidor::recibirDataGeneral(int client_socket)
{
    Comando comandito;

    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(struct Comando);
    bool client_socket_still_open = true;

    // Receive
    // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    // sockfd -> file descriptor that refers to a socket
    // buf -> where the received message into the buffer buf.
    // len -> The caller must specify the size of the buffer in len.
    // flags
    // The recv() call are used to receive messages from a socket.
    // If no messages are available at the socket, the receive call wait for a message to arrive. (Blocking)
    printf("numero del socket cliente que recibo= (%d ) \n", client_socket);

    while ((receive_data_size > bytes_receive) && client_socket_still_open)
    {
        printf("el servidor recibe del  socket del  cliente = (%d ) \n", this->client_socket);
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

    this->comando = comandito;
    return 0;
}
