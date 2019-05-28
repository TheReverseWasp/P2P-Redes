/* Client code in C */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

vector<int> ClientSockets;
vector<int> ServerSockets;
int TrackerSocket;
vector<thread> ThreadsRecibiendoClientes;
vector<thread> ThreadsEnviandoClientes;

vector<thread> ThreadsRecibiendoServidores;
vector<thread> ThreadsEnviandoServidores;


vector<thread> ThreadsRecibiendoTrackers;
vector<thread> ThreadsEnviandoTrackers;


vector<string> Files;
//thread para el traker.o
string ConvertSize(int n, int tam){
    string size = to_string(n);
    if(size.length() < tam){
        size = string(tam - size.length(), '0') + size;
    }
    return size;
}

char ReadByte(int Socket){//para leer todo el mensaje com oen el xl
    char * byte = new char;
    int n = recv(Socket, byte, 1, 0);
    if (n < 0){
        perror("Error reading message from socket");
    }
    char res;
    if(n > 0)
        res = *byte;
    else{
        res = '\0';
    }
    //cout << res << endl;
    delete byte;
    return res;
}

void MandarMensaje(int SocketClient, string mensaje){
    cout << "Mensaje a mandar: " << mensaje << endl;
    int n = send(SocketClient, mensaje.c_str(), mensaje.length(), 0);
    if(n < 0){
        perror("Error sending to socket");
    }
}

void ProcessMessage(int Socket, string Mensaje){//creo que esta funcion podria processar los mensajes que reciba de otros clientes, servidores y del trakcer, de esta forma la funcion recibiendo clientes se usa igual para estos tres casos

}

void RecibiendoCliente(int SocketClient){//socket donde mandare
//leer bye por byte
    char ultimobyte;
    char penultimocharbyte;
    //vector<char> request;
    string request;
    //si no ha habido un dobe salto de linea continuo leyendo
    bool leer = true;
    while(leer){
        char byte = ReadByte(SocketClient);
        if(byte){
            request += byte;
            //request.push_back(byte);
            if(request.size() > 0){
                if(request[request.length()-1] == '@'){
                    //leer = false;
                    ProcessMessage(SocketClient, request);
                    request = "";
                    //termine de leer
                    break;
                }
            }
        }
    }
}

void ListeningForNewClients(int SocketI){
    while(true){
        int in;
        in = accept(SocketI, NULL, NULL);//no conozco al participante activo
        //se supone que in, es un nuevo socket, el socket
        if (in < 0){
            perror("accept failed");
            //close(SocketI);
            exit(EXIT_FAILURE);
        }
        else{
            //CreatePlayer(in);//creao al jugador, con el socket que le corresponde, a la espera de recibir su avatar
            //cout << "Creando Player" << endl;

            ClientSockets.push_back(in);
            //thread ThreadRecibiendoCliente;
            //ThreadRecibiendoCliente = thread(RecibiendoCliente, in);
            ThreadsRecibiendoClientes.push_back(thread(RecibiendoCliente, in));

            //ThreadsEnviandoCliente.push_back(ThreadEnviando);
            //solo deberia haber un enviando
        }
    }
}

//necesito cone tarme a distintos servidores.
//debo tener en cuenta la desconeccion de cosas
//como me conecto al tracker??


int main(){
    int SocketServidor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//creando la interfaz
    if(SocketServidor == -1) {
        perror("can not create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in SSocketAddr;

    memset(&SSocketAddr, 0, sizeof(struct sockaddr_in));
    SSocketAddr.sin_family = AF_INET;
    SSocketAddr.sin_port = htons(1100);
    SSocketAddr.sin_addr.s_addr = INADDR_ANY;

    int status = bind(SocketServidor, (const struct sockaddr *)&SSocketAddr, sizeof(struct sockaddr_in));
    if(status == -1){
        perror("bind failed");
        close(SocketServidor);
        exit(EXIT_FAILURE); 
    }

    status = listen(SocketServidor, 10);
    if(status == -1) {
        perror("listen failed");
        close(SocketServidor);
        exit(EXIT_FAILURE);
    }
    //inciar mi modo servidor, escuchando clientes, que quieran los archivos que le he notifcado al tracker
    thread EsperandoClients (ListeningForNewClients, SocketServidor);
    cout << "iniciando servidor" << endl;
    //---------------------

    //comunicacino con tracker
    int SocketTracker = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);//creando la interfaz
    if(SocketTracker == -1) {
        perror("can not create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in SSocketAddrT;

    memset(&SSocketAddrT, 0, sizeof(struct sockaddr_in));
    SSocketAddrT.sin_family = AF_INET;
    SSocketAddrT.sin_port = htons(1100);
    //SSocketAddr.sin_addr.s_addr = INADDR_ANY;

    //int In = inet_pton(AF_INET, "192.168.1.9", &SSocketAddr.sin_addr);
    int In = inet_pton(AF_INET, "127.0.0.1", &SSocketAddrT.sin_addr);

    if (In < 0) {
        perror("first parameter is not a valid address family");
        close(SocketTracker);
        exit(EXIT_FAILURE);
    }
    else if (In == 0) {
        perror("char string (second parameter does not contain valid ipaddress");
        close(SocketTracker);
        exit(EXIT_FAILURE);
    }

    int status = connect(SocketTracker, (const struct sockaddr *)&SSocketAddrT, sizeof(struct sockaddr_in));
    if(status == -1){
        perror("connect failed");
        close(SocketTracker);
        exit(EXIT_FAILURE); 
    }

    TrackerSocket = SocketTracker;//guardando el socket del tracker
    ThreadsRecibiendoTrackers.push_back(thread(RecibiendoCliente, TrackerSocket));//creando el thread de recepcion del tracker
    //iniciar el thread que recibe
    //debe iniciar la coneccion con el tracker, en determinado ip, luego debo poder intercambiar mensajes con el
    //despues de conectarme, debo hacer una revision de los archivosque tengo, comunicarle al tracker
    //login
    string LoginMessage = "121.0.0.1#hola#@";
    MandarMensaje(TrackerSocket, "0" + ConvertSize(LoginMessage.size(), 3) + LoginMessage);
    //register
    string RegisterMessage = "121.0.0.1#hola#@";
    MandarMensaje(TrackerSocket, "2" + ConvertSize(LoginMessage.size(), 3) + RegisterMessage);
    // else register and login
    //entre en el tracker, lo interesante es el register

    for(int i = 0; i < Files.size(); i++){
        //RegisterItem();//encapsular en funciones?
    }

    //comunicandome con otros servidores
    //esto en funcion de,, debo tener mi funcion escuchar servidor

    //ahora debo iniciar mi modo cliente, 
    //aqui debo permitir que el usuario busque archivos, yo pedire al tracker la lista de servidores, y en mi modo cliente me conectare a ellos.
    while(true){
        cout << "ingresar nombre de archivo a buscar" << endl;
        string buscar;
        cin >> buscar; 
        //solicitar informacion al travker, es devir pedir la lista de servidores
        //creo que la lista de chunks tambien
        //despues de recibida, mandar a crear las conexiones con los servidores
    }

    //srand (time(NULL));
    //thread GameL (GameLoop);

    for(int i = 0; i < ThreadsRecibiendoClientes.size(); i++){
        ThreadsRecibiendoClientes[i].join();
    }

    //GameL.join();

    EsperandoClients.join();

    return 0;
}