/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#pragma once

#include "atomic_task.h"
#include "client.h"
#include "file.h"
#include "make_ip.h"
#include "message.h"
#include "socket.h"
#include <regex>

#include <iostream>
#include <string>

class LoguedActions {

 public:

   void ClientMenu();
   void BenderMenu();

   int get_value_client(){return value_client;}
   int get_value_bender(){return value_bender;}

   void LoguedClient (int v, int good_port, int dest_good_port, std::string& ip_address, Client& client);
   void LoguedBender (int v, int good_port, int dest_good_port, std::string& ip_address, Client& client);

   void ServerClient (int v, int good_port, int dest_good_port, std::string& ip_address);
   void ServerBender (int v, int good_port, int dest_good_port, std::string& ip_address);

  private:
    int value_client {-1};
    int value_bender {-1};
};