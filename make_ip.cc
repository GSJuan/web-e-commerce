/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#include "make_ip.h"

sockaddr_in 
MakeIp::make_ip_address(int port, const std::string& ip_address) {

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