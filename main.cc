/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#include "client.h"
#include "login_register.h"

#include <unistd.h>

#include <atomic>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <thread>



void 
LogReg(int good_port, int dest_good_port, std::exception_ptr& eptr, 
      std::string& ip_address, std::atomic_bool& close) {
  try {

    // Puntero a nuestra clase LoginRegister, si no es un puntero, el hilo no lo
    // acepta
    LoginRegister* LR = new LoginRegister;

    // Hilos que vamos a usar
    std::thread client;
    std::thread server;

    do {
      // Opciones
      LR->HowUse();

      // Lanzamos los hilos
      if (LR->get_Value() <= 4) {
        client = std::thread (&LoginRegister::LoginReg, LR, LR->get_Value(), 
                              good_port, dest_good_port, std::ref(ip_address));
        server = std::thread (&LoginRegister::ServerLoginReg, LR, LR->get_Value(), 
                              good_port, dest_good_port, std::ref(ip_address));
        // Esperamos a que los hilos acaben.
        server.join();
        client.join();
      }
      else close = true;

    } while (!close);

    delete LR;
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

  std::exception_ptr eptr {};
  std::atomic_bool close {false};

  // Creamos nuestro hilo que se encarga del Login/Registro.
  std::thread process1(&LogReg, good_port, dest_good_port, std::ref(eptr),
                       std::ref(ip_address), std::ref(close));
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
