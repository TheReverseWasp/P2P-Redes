#ifndef INTERMEDIAROS_CLIENT_H
#define INTERMEDIAROS_CLIENT_H

#include "functions.h"

using namespace std;

extern int my_l_port;
extern string my_ip;
extern string tracker_ip;
//
extern int procedure_part;
extern int attemps;
//
extern int slptime;


///llr basics client
extern void login();
extern void logout();
extern void register_myself();


#endif
