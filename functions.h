#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bits/stdc++.h>

using namespace std;

struct info{
  char msg_type;
  int size_of_message;
  vector<string> data; // data[0] = ip //data[1] = port always
  info();
  bool read_data(string message);
  info operator= (info ended);
};

struct file_info{
  vector<pair<string, int> > available_clients;
  map<pair<string, int>, bool> confirmed_clients
}

#endif
