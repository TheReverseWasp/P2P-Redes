#ifndef INTERMEDIAROS_CLIENT_H
#define INTERMEDIAROS_CLIENT_H

#include "functions.h"

using namespace std;

extern int my_l_port;
extern string my_ip;
extern string tracker_ip;
extern bool write_file;
extern mutex mtx;
//
extern int procedure_part;
extern int attemps;
//
extern int slptime;
//
extern vector<string> unresolved_file_names;
extern map<string, vector<pair<string, int> > >available_peers;

///llr basics client
extern void login();
extern void logout();
extern void register_myself();
///ask for information to the tracker
extern string generate_message(string doc_name, int i);
extern void send_and_reciv(string doc_name, int i)send_and_reciv(string doc_name, int i);
extern void ask_tracker();
extern bool ask_peer(string doc_name);
extern string gen_response(string text);
extern void listen_peer(int port_mafia);
extern void ask_tracker();

extern bool continue_flag;
#endif
