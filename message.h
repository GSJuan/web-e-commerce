/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <netinet/in.h>
#include <sys/socket.h>

#include <array>

struct Message {

  // Nuestra estructura va a poder almacenar 1024 caracteres.
  std::array<char, 1024> text;

  // Metodo que limpia nuestra estructura.
  void clear () {

    for (int travel = 0; travel < 1024; travel ++) 
      text[travel] = '\0';
  }

  uint32_t remote_ip;
  in_port_t remote_port;
};
#endif