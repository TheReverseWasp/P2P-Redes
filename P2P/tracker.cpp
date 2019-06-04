/* Client code in C */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"
#include <mutex>
#include <thread>
#include "intermediarios.h"
using namespace std;

string tracker_ip;

void define_local_variables() {
  cout << "ingrese el ip del tracker dice el tracker" << endl;
  cin >> tracker_ip;
}

int main(void)
{
  define_local_variables();
  

}
