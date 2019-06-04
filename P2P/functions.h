#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bits/stdc++.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fstream>

using namespace std;

extern int constant_size;
extern int always;
///
extern int tracker_port;
extern int ask_tracker_port;
///
//extern int reserved_listen_tracker;


struct info{
  char msg_type;
  int size_of_message;
  vector<string> data; // data[0] = ip //data[1] = port always
  info();
  bool read_data(string message);
};

struct file_info{
  vector<string> files;
  map<string, bool> registered;
};

///helper functions
extern int find_pair_str_int(vector<pair<string, int> > database, pair<string, int> x);
extern string fill_0z (int my_size);

///comunication functions
extern bool my_custom_send (string S_ip, int port_mafia, string message);
extern string my_custom_listen (int port_mafia);

#endif
