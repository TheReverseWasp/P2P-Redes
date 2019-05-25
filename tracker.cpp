/* Client code in C */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

using namespace std;

vector<info> llr_basics;
map<pair<string, int> > registered;
map<pair<string,int> , bool> loged_in;
int constant_size = 1005;

void log_in_listen(int port_mafia) {
  while (true) {
    while (true) {
      struct sockaddr_in stSockAddr;
      int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
      char buffer[256];
      int n;

      if(-1 == SocketFD)
      {
        perror("can not create socket");
        exit(EXIT_FAILURE);
      }

      memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

      stSockAddr.sin_family = AF_INET;
      stSockAddr.sin_port = htons(port_mafia);
      stSockAddr.sin_addr.s_addr = INADDR_ANY;
      
      if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
      {
        perror("error bind failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }

      if(-1 == listen(SocketFD, 10))
      {
        perror("error listen failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }

      for(;;)
      {
        int ConnectFD = accept(SocketFD, NULL, NULL);

        if(0 > ConnectFD)
        {
          perror("error accept failed");
          close(SocketFD);
          exit(EXIT_FAILURE);
        }


        bzero(buffer,256);
        n = read(ConnectFD,buffer,255);
        if (n < 0) perror("ERROR reading from socket");
        printf("Here is the message: [%s]\n",buffer);
        n = write(ConnectFD,"I got your message",18);
        if (n < 0) perror("ERROR writing to socket");

        /* perform read write operations ... */

        shutdown(ConnectFD, SHUT_RDWR);

        close(ConnectFD);
      }

      close(SocketFD);
    }

  }
}

void log_out_listen(int port_mafia) {

}

void register_listen(int port_mafia) {

}

void send_llr_basics(int port_mafia) {
  while (true) {
    for (int i = 0; i < llr_basics.size(); ) {
      string answer;
      pair<string, int> client_serv;
      client_serv.first = llr_basics[0].data[0];
      client_serv.second = stoi(llr_basics[0].data[1]);
      switch (llr_basics[i].msg_type) {
        case '0': //login
        if (registered[client_serv] == 1 && loged_in[client_serv] == 0) {
          //login
          answer = "4";
          loged_in[client_serv] = 1;
        }
        else {
          //ERROR
          answer = "N";
        }
        case '1':
        if (registered[client_serv] == 1 && loged_in[client_serv] == 1) {
          //logout
          answer = "5";
          loged_in[client_serv] = 0;
        }
        else{
          //ERROR
          answer = "N";
        }
        case '2':
        if (registered[client_serv] == 0) {
          //register
          answer = "5";
          registered[client_serv] = 1;
        }
        else{
          //ERROR
          answer = "N";
        }
      }
      answer += "@";


      struct sockaddr_in stSockAddr;
      int Res;
      int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
      int n;

      if (-1 == SocketFD)
      {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
      }

      memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

      stSockAddr.sin_family = AF_INET;
      stSockAddr.sin_port = htons(port_mafia);
      Res = inet_pton(AF_INET, "192.168.1.6", &stSockAddr.sin_addr);
      /*
      if (0 > Res)
      {
        perror("error: first parameter is not a valid address family");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }
      else if (0 == Res)
      {
        perror("char string (second parameter does not contain valid ipaddress");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }
      */
      if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
      {
        perror("connect failed");
        close(SocketFD);
        //exit(EXIT_FAILURE);
        llr_basics.erase(llr_basics.begin());
        break;
      }
      n = write(SocketFD, answer, answer.size());
      /* perform read write operations ... */

      shutdown(SocketFD, SHUT_RDWR);

      close(SocketFD);

      llr_basics.erase(llr_basics.begin());
    }
  }
}

int main(void)
{

}
