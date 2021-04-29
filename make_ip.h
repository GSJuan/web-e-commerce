/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstring>
#include <iostream>
#include <string>

class MakeIp {

  public:
    sockaddr_in make_ip_address(int port, const std::string& ip_address = 
                                std::string());
};