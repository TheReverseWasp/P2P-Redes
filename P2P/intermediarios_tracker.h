#ifndef INTERMEDIARIOS_TRACKER_H
#define INTERMEDIARIOS_TRACKER_H

#include "functions.h"

using namespace std;

///
extern map<pair<string, int>, bool > registered_database;
extern map<pair<string, int>, int> loged_in_database;
extern vector<pair<string, int> > loged_in_database_ph;

extern void llr_basics_tracker(string my_tracker_ip);
///
extern string generate_message_from_tracker(string tracker_ip, string doc_file);
extern string response_from_tracker_generator(string tracker_ip, vector<pair<string, int> > my_available_peers);
extern void listen_peers_ask_info (string tracker_ip);

#endif
