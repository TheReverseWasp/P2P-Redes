#ifndef INTERMEDIARIOS_TRACKER_H
#define INTERMEDIARIOS_TRACKER_H

#include "functions.h"

using namespace std;

extern int tracker_port;

///
extern map<pair<string, int> > registered_database;
extern map<pair<string, int>, bool> loged_in_database;

extern void llr_basics_tracker(string my_tracker_ip);


#endif
