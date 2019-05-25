#include "functions.h"

using namespace std;

bool info::read_data(string message) {
  if (message.find("@") == string::npos) {
    return 0;
  }
  msg_type = message[0];
  size_of_message = stoi(message.substr(1, 3));
  //the first element doesnt have # as predecesor
  message = message.subst(4, message.size() - 4);
  while (message[0] != "@") {
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

info operator= (info ended) {
  msg_type = ended.msg_type;
  size_of_message = ended.size_of_message;
  data.clear();
  for (int i = 0; i < ended.data.size(); i++) {
    data.push_back(ended.data[i]);
  }
  return this;
}
