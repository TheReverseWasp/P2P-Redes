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
#include <mutex>
#include <thread>
using namespace std;

mutex mtx;
vector<info> llr_basics;
map<pair<string, int> > registered;
map<pair<string,int> , bool> loged_in;
map<string, vector<string> > files_shasum;
map<pair<string,string>, file_info> registered_files;
int constant_size = 1005;
int always = 4;


void llr_basics_listen(int port_mafia) {
  while (true) {
    while (true) {
      struct sockaddr_in stSockAddr;
      int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
      char buffer[constant_size];
      char alw[always];
      int n;

      if(-1 == SocketFD)
      {
        perror("can not create socket");
        break;
        //exit(EXIT_FAILURE);
      }

      memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

      stSockAddr.sin_family = AF_INET;
      stSockAddr.sin_port = htons(port_mafia);
      stSockAddr.sin_addr.s_addr = INADDR_ANY;

      if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
      {
        perror("error bind failed");
        close(SocketFD);
        break;
        //exit(EXIT_FAILURE);
      }

      if(-1 == listen(SocketFD, 10))
      {
        perror("error listen failed");
        close(SocketFD);
        break;
        //exit(EXIT_FAILURE);
      }
      int ConnectFD = accept(SocketFD, NULL, NULL);

      if(0 > ConnectFD)
      {
        perror("error accept failed");
        close(SocketFD);
        break;
        //exit(EXIT_FAILURE);
      }


      bzero(buffer,constant_size);
      bzero(alw, always);
      n = read(ConnectFD,alw, always);
      if (n < 0) perror("ERROR reading from socket");
      printf("Here is the message: [%s]\n",alw);
      string message;
      for (size_t i = 0; i < always; i++) {
        buffer[i] = alw[i];
        message += buffer[i];
      }
      int left_blocks = stoi(message.subst(1, 3));
      int pos = 0;
      while (left_blocks > 0 && buffer[4 + pos] != '@') {
        n = read(ConnectFD,buffer, 1);
        message += buffer[4 + pos];
        pos++;
        left_blocks--;
      }
      shutdown(ConnectFD, SHUT_RDWR);

      close(ConnectFD);
      close(SocketFD);
      info my_object;
      my_object.read_data(message);
      llr_basics.push_back(my_object);
      cout << "mensaje recibido en llr basics: " << message << endl;
    }
  }
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
      n = write(SocketFD, answerc.str(), answer.size());
      /* perform read write operations ... */

      shutdown(SocketFD, SHUT_RDWR);

      close(SocketFD);

      llr_basics.erase(llr_basics.begin());
    }
  }
}

void register_item_listen

int port_mafia = 4000;
int sheeps = 5000;
int armed_agency = 6000;

int main(void)
{
  thread t1(llr_basics_listen, port_mafia);
  thread t2(send_llr_basics, port_mafia);

  t1.join();
  t2.join();
}
