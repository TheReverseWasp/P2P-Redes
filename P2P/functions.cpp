#include "functions.h"

using namespace std;

int tracker_port = 5555;
int ask_tracker_port = 5556;
//int reserved_listen_tracker = 5557;

int constant_size = 1005;
int always = 4;

info::info() {
  msg_type = 'N';
}
bool info::read_data(string message) {
  if (message.find("@") == string::npos) {
    return 0;
  }
  msg_type = message[0];
  size_of_message = stoi(message.substr(1, 3));
  //the first element doesnt have # as predecesor
  message = message.substr(4, message.size() - 4);
  while (message[0] != '@') {
    int pos = message.find("#");
    if (pos == string::npos) {
      cout << "no encontro el #" << endl;
      return 0;
    }
    string my_data = message.substr(0, pos);
    data.push_back(my_data);
    message = message.substr(pos + 1, message.size() - pos - 1);
  }
  return 1;
}

int find_pair_str_int(vector<pair<string, int> > database, pair<string, int> x) {
  int answer = -1;
  for (unsigned int i = 0; i < database.size(); i++) {
    if (database[i] == x) {
      answer = i;
      break;
    }
  }
  return answer;
}

string fill_0z(int my_size) {
  string answer = to_string(my_size);
  if (answer.size() > 3) {
    return "-";
  }
  while (answer.size() < 3) {
    answer = "0" + answer;
  }
  cout << " -----This message size is: " + answer + "----- " << endl;
  return answer;
}


bool my_custom_send(string S_ip, int port_mafia, string message) {
  struct sockaddr_in stSockAddr;
  int Res;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  int n;

  if (-1 == SocketFD)
  {
    cout << "error en la funcion enviar" << endl;
    perror("cannot create socket");
    return 0;
    //exit(EXIT_FAILURE);
  }

  memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(port_mafia);
  Res = inet_pton(AF_INET, S_ip.c_str(), &stSockAddr.sin_addr);

  if (0 > Res)
  {
    cout << "error en la funcion enviar" << endl;
    perror("error: first parameter is not a valid address family");
    close(SocketFD);
    return 0;
    //exit(EXIT_FAILURE);
  }
  else if (0 == Res)
  {
    cout << "error en la funcion enviar" << endl;
    perror("char string (second parameter does not contain valid ipaddress");
    close(SocketFD);
    return 0;
    //exit(EXIT_FAILURE);
  }

  if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
  {
    cout << "error en la funcion enviar" << endl;
    perror("connect failed");
    close(SocketFD);
    return 0;
    //exit(EXIT_FAILURE);
  }
  n = write(SocketFD,message.c_str(), message.size());
  /* perform read write operations ... */

  shutdown(SocketFD, SHUT_RDWR);

  close(SocketFD);
  return 1;
}

string my_custom_listen (int port_mafia) {
  struct sockaddr_in stSockAddr;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  char buffer[constant_size];
  int n;

  if(-1 == SocketFD)
  {
    perror("can not create socket");
    //exit(EXIT_FAILURE);
    return "X";
  }

  memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(port_mafia);
  stSockAddr.sin_addr.s_addr = INADDR_ANY;

  if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
  {
    //perror("error bind failed");
    close(SocketFD);
    //exit(EXIT_FAILURE);
    return "X";
  }

  if(-1 == listen(SocketFD, 10))
  {
    //perror("error listen failed");
    close(SocketFD);
    return "X";
    //exit(EXIT_FAILURE);
  }


  int ConnectFD = accept(SocketFD, NULL, NULL);

  if(0 > ConnectFD)
  {
    //perror("error accept failed");
    close(SocketFD);
    //exit(EXIT_FAILURE);
    return "X";
  }


  bzero(buffer, constant_size);
  n = read(ConnectFD, buffer, always);
  if (n < 0) {
    //perror("ERROR reading from socket");
    return "X";
  }
  string message;
  for (size_t i = 0; i < always; i++) {
    message += buffer[i];
  }
  int left_sz = stoi(message.substr(1, 3));
  cout << "my_left_size " <<left_sz << endl;
  while (left_sz > 0 && buffer[0] != '@') {
    bzero(buffer, constant_size);
    n = read(ConnectFD, buffer, 1);
    if (n < 0) {
      //perror("ERROR reading from socket");
      return "X";
    }
    message += buffer[0];
    --left_sz;
  }

  /* perform read write operations ... */

  shutdown(ConnectFD, SHUT_RDWR);

  close(ConnectFD);

  close(SocketFD);
  cout << "aqui esta el mensaje : " + message << endl;
  return message;
}
