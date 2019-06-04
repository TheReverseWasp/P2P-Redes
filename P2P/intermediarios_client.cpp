#include "intermediarios_client.h"

int my_l_port;
string my_ip;
string tracker_ip;
bool write_file = 0;
//
int procedure_part = 0;
int attemps = 3;
//
int slptime = 1000000;

bool continue_flag = 1;

mutex mtx;

vector<string> unresolved_file_names;
map<string, vector<pair<string, int> > >available_peers;

///llr basics client
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
  string variable_part = my_ip + "#" + to_string(my_l_port) + "#@";
  message += to_string(variable_part.size()) + variable_part;
  int try_1 = 0, try_2 = 0;
  while (try_1 < attemps) {
    usleep(slptime);
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
    usleep(slptime);
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
  string variable_part = my_ip + "#" + to_string(my_l_port) + "#@";
  message += to_string(variable_part.size()) + variable_part;
  int try_1 = 0, try_2 = 0;
  while (try_1 < attemps) {
    usleep(slptime);
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
    usleep(slptime);
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
  string variable_part = my_ip + "#" + to_string(my_l_port) + "#@";
  message += to_string(variable_part.size()) + variable_part;
  int try_1 = 0, try_2 = 0;
  while (try_1 < attemps) {
    usleep(slptime);
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
    usleep(slptime);
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

///client to client conversation
string generate_message(string doc_name, int i) {
  string message = "A";
  string variable_part = my_ip + "#" + to_string(available_peers[doc_name][i].second) + "#" + doc_name + "#@";
  message += fill_0z(variable_part.size()) + variable_part;
  return message;
}

void send_and_reciv(string doc_name, int i) {
  bool confirmed = my_custom_send(available_peers[doc_name][i].first,
  available_peers[doc_name][i].second, generate_message(doc_name, i));
  if (confirmed == 0) {
    cout << "peer " + available_peers[doc_name][i].first + "-" << available_peers[doc_name][i].second << " is unactive" << endl;
    return;
  }
  string message = my_custom_listen(available_peers[doc_name][i].second);
  info my_info;
  if (my_info.read_data(message) == 0) {
    cout << "response is corrupted from peer " + available_peers[doc_name][i].first + "-" << available_peers[doc_name][i].second << endl;
    return;
  }
  mtx.lock();
  if (write_file == 0) {
    filebuf fb;
    fb.open (doc_name,std::ios::out);
    ostream my_file(&fb);
    for (unsigned int i = 2; i < my_info.data.size(); i++) {
      my_file << my_info.data[i] << '\n'; //future correction
    }
    fb.close();
    write_file = 1;
  }
  mtx.unlock();
}

bool ask_peer(string doc_name) {
  bool is_ok = 0;
  vector<thread> my_v_thread;
  for (unsigned int i = 0; i < available_peers[doc_name].size(); i++) {
    my_v_thread.push_back(thread(send_and_reciv, doc_name, i));
  }
  for (unsigned int i = 0; i < my_v_thread.size(); i++) {
    my_v_thread[i].join();
  }
  if (write_file == 1) {
    write_file = 0;
    is_ok = 1;
  }
  return is_ok;
}

string gen_response (string text) {
  string answer = "F";
  string variable_part = my_ip + "#" + to_string(my_l_port) + "#" + text + "#@";
  answer += to_string(variable_part.size()) + variable_part;
  return answer;
}
void listen_peer(int port_mafia) {
  while (continue_flag == 1) {
    string message = my_custom_listen(port_mafia);
    if (message[0] != 'X') {
      info my_info;
      if (my_info.read_data(message) == 1) {
        filebuf fb;
        if (fb.open(my_info.data[3], ios::in)) {
          istream my_file(&fb);
          string temp, acum;
          while (getline(my_file, temp) && acum.size() < 980) {
            acum += temp;
          }
          fb.close();
          if (acum.size() > 980) {
            acum = acum.substr(0, 980);
          }
          string my_response = gen_response(acum);
          my_custom_send(my_info.data[0], stoi(my_info.data[1]), my_response);

        }
        else {
          cout << "error al abrir el documento" << endl;
        }
      }
    }
  }
  return;
}

///ask for information to the tracker
void ask_tracker () {
  //cout << "indique su IP dice el nomo" << endl;
  //cin >> my_ip;
  string doc_name;
  cout << "indique el nombre del documento que desea obtener" << endl;
  cin >> doc_name;
  unresolved_file_names.push_back(doc_name);
  ///building message1
  string message = "3";
  string variable_part = my_ip + "#" + to_string(my_l_port) + "#" +
  doc_name +"#@";
  message += to_string(variable_part.size()) + variable_part;
  int try_1 = 0, try_2 = 0;
  string message_I_hear;
  while (try_1 < attemps) {
    usleep(slptime);
    cout << "send register attemp " << try_1 << endl;
    bool answer = my_custom_send(tracker_ip, ask_tracker_port, message);
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
    usleep(slptime);
    cout << "recv register attemp " << try_2 << endl;
    message_I_hear = my_custom_listen(ask_tracker_port);
    if (message_I_hear[0] != 'X') {
      break;
    }
    try_2++;
  }
  if (try_2 == attemps) {
    cout << "error al recivir" << endl;
    return;
  }
  cout << "success" << endl;
  info my_info;
  my_info.read_data(message_I_hear);
  for (unsigned int i = 2; i < my_info.data.size(); i+=2) {
    pair<string, int> temp;
    temp.first = my_info.data[i];
    temp.second = stoi(my_info.data[i + 1]);
    available_peers[doc_name].push_back(temp);
  }
  /////call function for all pears here
  if (ask_peer(doc_name) == 0) {
    cout << "No se encontro el documento o no se encontraron peers disponibles" << endl;
  }
  else {
    cout << "documento conseguido!!!" << endl;
  }
  ///to hear
}
