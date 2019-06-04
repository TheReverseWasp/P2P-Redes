/* Client code in C */

#include "intermediarios_tracker.h"
using namespace std;

string tracker_ip;

void define_local_variables() {
  cout << "ingrese el ip del tracker dice el tracker" << endl;
  cin >> tracker_ip;
}

int main(void)
{
  define_local_variables();
  thread th1(llr_basics_tracker, tracker_ip);
  thread th2(listen_peers_ask_info, tracker_ip);
  th1.join();
  th2.join();
}
