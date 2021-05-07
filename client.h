/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#pragma once

#include <string>

class Client {
  
  public:
    void Clean ();

    void set_Password (std::string&);
    void set_Email (std::string&);

    std::string& get_Password ();
    std::string& get_email ();

    bool exito {false};
    bool vendedor {false};
  private:
    std::string password{""};
    std::string email{""};
};