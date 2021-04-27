/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc
   Ejecutar:    ./Netcp
*/

#include "atomic_task.h"
#include "file.h"
#include "general_methods.h"
#include "socket.h"



void 
LoginRegister (int good_port, int dest_good_port, std::exception_ptr& eptr, 
      std::string& ip_address, std::atomic_bool& close) {

  try {
  }

  catch (...) {
    eptr = std::current_exception();
  }
}



int 
protected_main (int argc, char* argv[]) {

  std::string help = "--help";

  // Si el usuario escribe --help.
  if (argc == 2 && argv[1] == help) {
 
    throw std::invalid_argument("Este programa mediante un socket envía la "
          "información de un .txt a otro socket que guarda el mensaje en un"
          " .txt");
  }

  std::string port;
  std::string ip_address;
  std::string dport;

  // Si las variables de entorno no tienen ningun valor les damos nosotros uno.
  char * dest_port = getenv ("NETCP_DEST_PORT");
  if (dest_port == NULL)
    dport = "0";
  else 
    dport = dest_port;

  char * dest_ip = getenv ("NETCP_DEST_IP");
  if (dest_ip == NULL)
    ip_address= "127.0.0.1";
  else 
    ip_address = dest_ip;

  char * cport = getenv ("NETCP_DEST_PORT");
  if (cport == NULL)
    port = "8000";
  else 
    port = cport;

  // Comprobamos que se nos haya pasado un puerto "válido".
  for (unsigned travel = 0; travel < port.size(); travel++) {
    if (!std::isdigit(port[travel]))
      throw std::invalid_argument("Introduzca un puerto valido."
      "Por ejemplo: 8000, 9500 ...");
  }

  // Comprobamos que se nos haya pasado un puerto "válido".
  for (unsigned travel = 0; travel < dport.size(); travel++) {
    if (!std::isdigit(dport[travel]))
      throw std::invalid_argument("Introduzca un puerto valido."
      "Por ejemplo: 8000, 9500 ...");
  }

  // Pasamos el puerto del string a un int.
  int good_port = std::stoi(port);
  int dest_good_port = std::stoi(dport);

  // Creamos nuestro manejador de sañales.
  struct sigaction act {0};
  act.sa_handler = &ActSignal;
  sigaction (SIGUSR1, &act, NULL);

  // Creamos nuestro manejador de señales y bloqueamos las señales que no nos
  // interesen.
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  sigaddset(&set, SIGTERM);
  sigaddset(&set, SIGHUP);
  pthread_sigmask(SIG_BLOCK, &set, NULL);

  std::exception_ptr eptr {};
  std::atomic_bool close {false};

  // Creamos nuestro hilo que se encarga del Login/Registro.
  std::thread process1(&LoginRegister, good_port, dest_good_port, std::ref(eptr),
                       std::ref(ip_address), std::ref(close));

  // Creamos el hilo encargado de indicar que el programa debe acabar si recibe
  // una de las señales bloqueadas arriba.
  std::thread close_signal (&Signal, std::ref(set), std::ref(close), 
                            std::ref(process1));
  close_signal.detach();

  process1.join();
  
  if (eptr)
    std::rethrow_exception(eptr);

  return 0;
}



// Tratamiento de errores.
int 
main(int argc, char* argv[]) {

  try {
    return protected_main (argc, argv);
  }

  catch (std::invalid_argument& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
  catch (std::system_error& error) {
    if (error.code().value() != EINTR)
      std::cerr << error.what() << '\n';
    return 2;
  }
  catch (...) {
    std::cerr << "¡¡¡ ERROR DESCONOCIDO !!!" << '\n';
  }
  return 0;
}