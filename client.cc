/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#include "client.h"

void Client::Clean () {

  password = "";
  email = "";
}

void 
Client::set_Password (std::string& aux) {

  password = aux;
}



void 
Client::set_Email (std::string& aux) {

  email = aux;
}



std::string&
Client::get_Password () {

  return password;
}



std::string&
Client::get_email () {

  return email;
}