#include "intermediarios.h"

int my_l_port;
int tracker_port = 5555;
string my_ip;
string tracker_ip;
//
int procedure_part = 0;
int attemps = 3;
//
int slptime = 1000;


void register_myself() {
  ///default input
  cout << "indique su IP dice el nomo" << endl;
  cin >> my_ip;
  cout << "indique el puerto que utilizara dice el saltamontes" << endl;
  cin >> my_l_port;
  cout << "indique el ip del tracker dice el sensei" << endl;
  cin >> tracker_ip;
  ///building message1
  string message = "2";
  string variable_part = my_ip + "#" + to_string(my_l_port) + "@";
  message += to_string(variable_part.size()) + variable_part;
  int try_1 = 0, try_2 = 0;
  while (try_1 < attemps) {
    sleepcp(slptime);
    cout << "send register attemp " << try_1 << endl;
    bool answer = my_custom_send(tracker_ip, tracker_port, message);
    if (answer == 1) {
      break;
    }
    try_1++;
  }
  if (try_1 == attemps) {
    cout << "error al enviar" << endl;
    return;
  }
  cout << "success" << endl;
  while (try_2 < attemps) {
    sleepcp(slptime);
    cout << "recv register attemp " << try_2 << endl;
    string answer = my_custom_listen(tracker_port);
    if (answer[0] != 'N') {
      break;
    }
    try_2++;
  }
  if (try_2 == attemps) {
    cout << "error al recivir" << endl;
    return;
  }
  cout << "success" << endl;
}

void login() {
  cout << "indique su IP dice el nomo" << endl;
  cin >> my_ip;
  cout << "indique el puerto que utilizara dice el saltamontes" << endl;
  cin >> my_l_port;
  cout << "indique el ip del tracker dice el sensei" << endl;
  cin >> tracker_ip;
  ///building message1
  string message = "0";
  string variable_part = my_ip + "#" + to_string(my_l_port) + "@";
  message += to_string(variable_part.size()) + variable_part;
  int try_1 = 0, try_2 = 0;
  while (try_1 < attemps) {
    sleepcp(slptime);
    cout << "send register attemp " << try_1 << endl;
    bool answer = my_custom_send(tracker_ip, tracker_port, message);
    if (answer == 1) {
      break;
    }
    try_1++;
  }
  if (try_1 == attemps) {
    cout << "error al enviar" << endl;
    return;
  }
  cout << "success" << endl;
  while (try_2 < attemps) {
    sleepcp(slptime);
    cout << "recv register attemp " << try_2 << endl;
    string answer = my_custom_listen(tracker_port);
    if (answer[0] != 'N') {
      break;
    }
    try_2++;
  }
  if (try_2 == attemps) {
    cout << "error al recivir" << endl;
    return;
  }
  cout << "success" << endl;
}

void logout() {
  cout << "indique su IP dice el nomo" << endl;
  cin >> my_ip;
  cout << "indique el puerto que utilizara dice el saltamontes" << endl;
  cin >> my_l_port;
  ///building message1
  string message = "1";
  string variable_part = my_ip + "#" + to_string(my_l_port) + "@";
  message += to_string(variable_part.size()) + variable_part;
  int try_1 = 0, try_2 = 0;
  while (try_1 < attemps) {
    sleepcp(slptime);
    cout << "send register attemp " << try_1 << endl;
    bool answer = my_custom_send(tracker_ip, tracker_port, message);
    if (answer == 1) {
      break;
    }
    try_1++;
  }
  if (try_1 == attemps) {
    cout << "error al enviar" << endl;
    return;
  }
  cout << "success" << endl;
  while (try_2 < attemps) {
    sleepcp(slptime);
    cout << "recv register attemp " << try_2 << endl;
    string answer = my_custom_listen(tracker_port);
    if (answer[0] != 'N') {
      break;
    }
    try_2++;
  }
  if (try_2 == attemps) {
    cout << "error al recivir" << endl;
    return;
  }
  cout << "success" << endl;
}
