#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bits/stdc++.h>

using namespace std;

extern int constant_size = 1005;
extern int always = 4;
///
extern int tracker_port;
extern int ask_tracker_port;
///


struct info{
  char msg_type;
  int size_of_message;
  vector<string> data; // data[0] = ip //data[1] = port always
  info();
  bool read_data(string message);
  info operator= (info ended);
};

struct file_info{
  vector<pair<string, int> > files;
  map<pair<string, int>, bool> registered;
};

string fill_0z (int my_size);

string my_custom_send (string S_ip, int port_mafia, string message);
string my_custom_listen (int port_mafia);

#endif
