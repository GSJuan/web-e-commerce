/* Univerdidad:Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Asignatura Sistemas Operativos (SSOO).
   Autor:       Alejandro Lugo Fumero.
   Correo:      alu0101329185@ull.edu.es
   Práctica nº: 3
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc
   Ejecutar:    ./Netcp
*/

#pragma once

#include "message.h"

#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>

class Socket {
  
  public:
	  Socket(const sockaddr_in& address);
	  ~Socket();

    void SendTo(const Message& message, const sockaddr_in& address);
	  void ReceiveFrom(Message& message, sockaddr_in& address);

  private:
	  int fd_;
};
