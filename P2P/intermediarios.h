#ifndef INTERMEDIAROS_H
#define INTERMEDIAROS_H

#include "functions.h"

using namespace std;

extern int my_l_port;
extern int tracker_port;
extern string my_ip;
extern string tracker_ip;
//
extern int procedure_part;
extern int attemps;
//
extern int slptime;


void login();
void logout();
void register_myself();


#endif
