#include "functions.h"

using namespace std;

void info::read_data(string message) {
  msg_type = message[0];
  size_of_message = stoi(message.substr(1, 3));
  //the first element doesnt have # as predecesor
  message = message.subst(4, message.size() - 4);
  while (message[0] != "@") {
    int pos = message.find("#");
    string my_data = message.substr(0, pos);
    data.push_back(my_data);
    message = message.substr(pos + 1, message.size() - pos - 1);
  }
}
