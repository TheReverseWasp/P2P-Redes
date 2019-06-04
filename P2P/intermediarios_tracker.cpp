#include "intermediarios_tracker.h"

using namespace std;

///vars
map<pair<string, int>, bool > registered_database;
map<pair<string, int>, int> loged_in_database;
vector<pair<string, int> > loged_in_database_ph;

///llr basics tracker

void llr_basics_tracker(string my_tracker_ip) {
  while (true) {
    string temp = my_custom_listen(tracker_port);
    cout << "the message is: " << temp << endl;
    info my_listener;
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
          loged_in_database_ph.push_back(my_register_data);
          proceed_flag = 4;
        }
        break;
        case '1': ///logout
        if (registered_database[my_register_data] == 1 &&
        loged_in_database[my_register_data] == 1) {
          loged_in_database[my_register_data] = 0;
          proceed_flag = 5;
          if (find_pair_str_int(loged_in_database_ph, my_register_data) != -1) {          /* code */
            loged_in_database_ph.erase(loged_in_database_ph.begin() +
            find_pair_str_int(loged_in_database_ph, my_register_data));
          }
        }
        break;
        case '2': ///register
        if (registered_database[my_register_data] == 0) {
          registered_database[my_register_data] = 1;
          proceed_flag = 6;
        }
        break;
        default:
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
    else {
      cout << "error leyendo el mensaje : " << temp << endl;
    }
  }
  return;
}

////asking part
string generate_message_from_tracker(string tracker_ip, string doc_file) {
  string answer = "M";
  string variable_part = tracker_ip + "#" + to_string(ask_tracker_port) + "#" + doc_file + "#@";
  answer += fill_0z(variable_part.size()) + variable_part;
  return answer;
}

string response_from_tracker_generator(string tracker_ip, vector<pair<string, int> > my_available_peers) {
  string answer = "I";
  string variable_part = tracker_ip + "#" + to_string(ask_tracker_port) + "#";
  for (unsigned int i = 0; i < my_available_peers.size(); i++) {
    if (variable_part.size() > 980) {
      break;
    }
    variable_part += my_available_peers[i].first + "#" + to_string(my_available_peers[i].second) + "#";
  }
  variable_part += "@";
  answer += fill_0z(variable_part.size()) + variable_part;
  return answer;
}

void listen_peers_ask_info (string tracker_ip) {
  while (true) {
    string message = my_custom_listen(ask_tracker_port);
    vector<pair<string, int> > response_peers;
    if (message[0] != 'X') {
      info my_info;
      if (my_info.read_data(message) == 1) {
        for (unsigned int i = 0; i < loged_in_database_ph.size(); i++) {
          if (my_custom_send(loged_in_database_ph[i].first,
            loged_in_database_ph[i].second,
            generate_message_from_tracker(tracker_ip, my_info.data[3])) == 1) {
              string response = my_custom_listen(loged_in_database_ph[i].second);
              if (response[0] != 'X' && response[0] != 'N') {
                response_peers.push_back(loged_in_database_ph[i]);
              }
            }
          }
          if (my_custom_send(my_info.data[0], stoi(my_info.data[1]), response_from_tracker_generator(tracker_ip, response_peers)) == 0) {
            cout << "error al enviar la respuesta" << endl;
          }
          else {
            cout << "exito al enviar la respuesta : " << response_from_tracker_generator(tracker_ip, response_peers) << endl;
          }
        }
      }
    }
  }
