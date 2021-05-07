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

class LoginRegister {

  public:

    void HowUse ();

    int get_Value();

    void LoginReg (int v, int good_port, int dest_good_port, std::string& ip_address, Client& client);
    void ServerLoginReg (int v, int good_port, int dest_good_port, std::string& ip_address);

    std::string ReturnEmail(std::array<char, 1024>& text);

  private:
    int value {-1};
    //Client client;
};