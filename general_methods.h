/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Algoritmos y estructuras de datos avanzadas
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc
   Ejecutar:    ./Netcp
*/

#ifndef GENERALMETHODS_H
#define GENERALMETHODS_H

#include <arpa/inet.h>
#include <netinet/in.h>

#include <atomic>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

sockaddr_in 
make_ip_address(int port, const std::string& ip_address = 
                            std::string()) {

  sockaddr_in address{};
  // Nuestros socket son de la familia AF_INET ya que usamos TCP/IP.
  address.sin_family = AF_INET ;

  // Miramos que el valor del puerto sea correcto.
  if (port < 0 || port > 65525)
    throw std::invalid_argument("El valor del puerto es ERRONEO, pruebe"
          " con un puerto entre 1 y 65525, ó 0 si quieres que el sistema"
          " operativo asigne uno cualquiera que esté disponible");
  else
    address.sin_port = htons(port);

  // Miramos si "ip_address" está vacío.
  if (ip_address.size() == 0)
    address.sin_addr.s_addr = htonl(INADDR_ANY);
  // Si no está vacío convertimos el string a char* y utilizamos inet_aton.
  else {
    char ip[ip_address.size()];
    strcpy(ip, ip_address.c_str());

    if (inet_aton(ip, &address.sin_addr) == 0)
      throw std::invalid_argument("La dirrección ip introducida es "
      "ERRONEA o tiene un formato erroneo, un ejemplo de una ip válida "
      "sería: 192.168.1.68");
  }

  return address;
}


// Método que usa el hilo que espera hasta recibir alguna señal delas bloqueadas
// previamente.
void
Signal (sigset_t& set, std::atomic_bool& close, std::thread& process1) {

  int signum;
  sigwait(&set, &signum);
  // Cuando recibamos esas señales indicamos al hilo que lee de teclado que
  // tiene que acabar.
  close = true;
  // Usamos esta señal para detener la espera de "std::cin" y que el hilo pueda
  // indicar al resto que acaben.
  pthread_kill(process1.native_handle(), SIGUSR1);
}



void 
ActSignal (int signum) {

  // Método que sirve comprobar que la señal SIGUSR1 funciona correctamente.
  const char* text;
  text = "---INTERRUMPIENDO---\n";
  write(STDOUT_FILENO, text, strlen(text));
}



// Método que separa lo que escribamos en teclado en dos std::string para su
// posterior uso.
void
SeparateString (std::string& read_keyboard, std::string& data) {

  int part = 0;
  std::string aux, aux1;
  for (unsigned travel = 0; travel < read_keyboard.size(); travel++) {
    if (read_keyboard[travel] != ' ')
      aux.push_back(read_keyboard[travel]);
    if (read_keyboard[travel] == ' ')
      part ++;
    if (part == 1) {
      aux1 = aux;
      aux.clear();
      part ++;
    }
  }
  if (aux1.size() != 0 && aux.size() != 0) {
    data = aux;
    read_keyboard = aux1;
  }
  aux.clear();
  aux1.clear();
}



// Metodo que devuelve true si el segundo argumento introducido por teclado es
// un número.
bool 
IsANumber (std::string& data) {

  if (data.empty())
    return false;

  for (unsigned travel = 0; travel < data.size(); travel++)
    if (!std::isdigit(data[travel]))
      return false;

  return true;
}
#endif
