#include "intermediarios_tracker.h"

using namespace std;

///llr basics tracker

void llr_basics_tracker(string my_tracker_ip) {
  while (true) {
    string temp = my_custom_listen(tracker_port);
    info my_listener();
    int proceed_flag = 0;
    if (my_listener.read_data(temp) == 1) {
      pair<string, int> my_register_data;
      my_register_data.first = my_listener.data[0];
      my_register_data.second = stoi(my_listener.data[1]);
      switch (my_listener.msg_type) {
        case '0': ///login
        if (registered_database[my_register_data] == 1 &&
        loged_in_database[my_register_data] == 0) {
          loged_in_database[my_register_data] = 1;
          proceed_flag = 4;
        }
        break;
        case '1': ///logout
        if (registered_database[my_register_data] == 1 &&
        loged_in_database[my_register_data] == 1) {
          loged_in_database[my_register_data] = 0
          proceed_flag = 5;
        }
        break;
        case '2': ///register
        if (registered_database[my_register_data] == 0) {
          registered_database[my_register_data] = 1;
          proceed_flag = 6;
        }
        break;
      }
      string message;
      if (proceed_flag == 0) {
        message += "N";
      }
      else {
        message += to_string(proceed_flag);
      }
      string variable_part = my_tracker_ip + "#" + to_string(tracker_port) + "#@";
      message += fill_0z(variable_part.size()) + variable_part;
      my_custom_send(my_register_data.first, tracker_port, message);
    }
  }
  return;
}
