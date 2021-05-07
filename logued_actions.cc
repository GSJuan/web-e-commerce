/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#include "logued_actions.h"

void LoguedActions::ClientMenu() {

  std::string read;
  value_client = -1;
  do {
    std::cout << "Introduzca:\n0.Cerrar sesion\n1. Ver catalogo\n2. Comprar producto\n3. Ver datos\n";
    std::cin >> read;
    if (std::isdigit(read[0]) && read.size() == 1)
      value_client = read[0] - '0';
    read.clear();
  } while (value_client > 0);
}

void LoguedActions::BenderMenu() {
  std::string read;
  value_bender = -1;
  do {
    std::cout << "Introduzca:\n0.Cerrar sesion\n1. Ver catalogo\n2. Publicar producto\n3. Ver datos\n";
    std::cin >> read;
    if (std::isdigit(read[0]) && read.size() == 1)
      value_bender = read[0] - '0';
    read.clear();
  } while (value_bender > 0);
}

void LoguedActions::LoguedClient (int v, int good_port, int dest_good_port, std::string& ip_address, Client& client) {

}

void LoguedActions::LoguedBender (int v, int good_port, int dest_good_port, std::string& ip_address, Client& client) {

}

void LoguedActions::ServerClient (int v, int good_port, int dest_good_port, std::string& ip_address) {

}

void LoguedActions::ServerBender (int v, int good_port, int dest_good_port, std::string& ip_address) {

}