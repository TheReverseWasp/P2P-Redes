/* Client code in C */
#include "intermediarios_client.h"

using namespace std;

file_info my_file_info;

void register_file() {
  string file_name;
  cout << "ingrese el nombre del archivo" << endl;
  cin >> file_name;
  if (my_file_info.registered[file_name] == 0) {
    my_file_info.registered[file_name] = 1;
    my_file_info.files.push_back(file_name);
  }
  return;
}

bool loged_in = 0;

void driver_client() {
  int opcion;
  int port_mafia;
  vector<thread> my_threads;
  do{
    cout << "que desea hacer" << endl;
    cout << "1. registrarse" << endl;
    cout << "2. logearse" << endl;
    cout << "3. desloguearse" << endl;
    cout << "4. registrar un file" << endl;
    cout << "5. buscar un file en la red" << endl;
    cin >> opcion;
    switch (opcion) {
      case 1:
      register_myself();
      break;
      case 2:
      login();
      cout << "ingrese el puerto nuevamente" << endl;
      cin >> port_mafia;
      my_threads.push_back(thread(listen_peer, port_mafia));
      break;
      case 3:
      logout();
      break;
      case 4:
      register_file();
      break;
      case 5:
      ask_tracker();
      break;
      default:
      break;
    }
  } while (opcion < 6 && opcion > 0);
  continue_flag = 0;
  for (unsigned int i = 0; i < my_threads.size(); i++) {
    my_threads[i].join();
  }
}

int main(void)
{
  driver_client();
}
