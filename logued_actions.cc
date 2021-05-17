/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#include "logued_actions.h"
#include <cstring>

void LoguedActions::ClientMenu() {

  std::string read;
  value_client = -1;
  do {
    std::cout << "Introduzca:\n0. Cerrar sesion\n1. Ver catalogo\n2. Comprar producto\n3. Ver datos\n4. Modificar contraseña\n5. Borrar cuenta\n";
    std::cin >> read;
    if (std::isdigit(read[0]) && read.size() == 1)
      value_client = read[0] - '0';
    read.clear();
  } while (value_client < 0 || value_client > 5);
}

void LoguedActions::BenderMenu() {
  std::string read;
  value_bender = -1;
  do {
    std::cout << "Introduzca:\n0. Cerrar sesion\n1. Ver catalogo\n2. Publicar producto\n3. Ver datos\n4. Modificar contraseña\n5. Borrar cuenta\n";
    std::cin >> read;
    if (std::isdigit(read[0]) && read.size() == 1)
      value_bender = read[0] - '0';
    read.clear();
  } while (value_bender < 0 || value_bender > 5);
}

void LoguedActions::LoguedClient (int v, int good_port, int dest_good_port, std::string& ip_address, Client& client) {
try {
     // Creamos las estructuras.
    sockaddr_in socket_local_address {};
    sockaddr_in socket_remote_address {};

    MakeIp make;
    // Rellenamos las estructuras.
    socket_local_address = make.make_ip_address (good_port, "127.0.0.1");
    socket_remote_address = make.make_ip_address (0, ip_address);

    // Creamos el socket.
    Socket socket_remote (socket_remote_address);

    // Creamos la estructura que va a almacenar el mensaje.
    Message message {};
  std::regex pass_expr ("^(?=\\w*\\d)(?=\\w*[A-Z])(?=\\w*[a-z])\\S{3,10}$");
  int contador = 0;
  std::string temp, data;

  switch(v) { 
    case 0: //salir de este menu
      std::cout << "\n\n\n\n";
      break;

    case 1: //ver catalogo
      std::cout << "\n\n\n\n";
      break;
    case 2: //comprar producto
      std::cout << "\n\n\n\n";
      break;   

    case 3: //ver sus datos
      std::cout << "Direccion de correo: " << client.get_email() << "\n Contraseña: " << client.get_Password() << std::endl;
      break;

    case 4: //modificar contraseña
      
      do {
       std::cout << "\nIntroduzca su nueva contraseña (entre 3 y 10 caracteres, un numero, una mayúscula y una minúscula):\n";
      std::cin >> temp;
       contador ++;
       if(contador > 2) {
         contador = 0;
         std::cout<<"La contraseña solo debe y puede contener al menos:"<< 
         "\nUn numero, una mayúscula y una minúscula\n";
       }
      } while (!regex_match (temp, pass_expr));
      data = client.get_email() + " " + temp + " CL";

      for (unsigned travel = 0; travel < data.size(); travel ++) 
      message.text[travel] = data[travel];
      socket_remote.SendTo(message, socket_local_address);    
      message.clear();
      client.set_Password(temp);
      temp.clear();
      std::cout << "\nCambio realizado con exito";
      break;
    case 5:
      data = client.get_email() + " " + client.get_Password() + " CL";

      for (unsigned travel = 0; travel < data.size(); travel ++) 
        message.text[travel] = data[travel];
      
      socket_remote.SendTo(message, socket_local_address);    
      message.clear();
      client.Clean();
    break;
    default:
      break;
  }
  
}
catch (std::invalid_argument& error) {
    std::cerr << error.what() << '\n';
  }
  catch (std::system_error& error) {
    std::cerr << error.what() << '\n';
  }
  catch (...) {
    std::cerr << "¡¡¡ ERROR DESCONOCIDO !!!" << '\n';
  }
}

void LoguedActions::LoguedBender (int v, int good_port, int dest_good_port, std::string& ip_address, Client& client) {
try {
     // Creamos las estructuras.
    sockaddr_in socket_local_address {};
    sockaddr_in socket_remote_address {};

    MakeIp make;
    // Rellenamos las estructuras.
    socket_local_address = make.make_ip_address (good_port, "127.0.0.1");
    socket_remote_address = make.make_ip_address (0, ip_address);

    // Creamos el socket.
    Socket socket_remote (socket_remote_address);

    // Creamos la estructura que va a almacenar el mensaje.
    Message message {};
  std::regex pass_expr ("^(?=\\w*\\d)(?=\\w*[A-Z])(?=\\w*[a-z])\\S{3,10}$");
  int contador = 0;
  std::string temp, data, product;

  switch(v) { 
    case 0: //salir de este menu
      std::cout << "\n\n\n\n";
      break;

    case 1: //ver catalogo
      std::cout << "\n\n\n\n";
      break;
    case 2: //publicar producto
      std::cout << "\nIntroduzca el producto a publicar:";
      std::cin >> product;
      data = client.get_email() + " " + product;
      for (unsigned travel = 0; travel < data.size(); travel ++) 
        message.text[travel] = data[travel];
      socket_remote.SendTo(message, socket_local_address);    
      message.clear();
      std::cout << "\nProducto publicado con exito\n";
      break;   

    case 3: //ver sus datos
      std::cout << "Direccion de correo: " << client.get_email() << "\n Contraseña: " << client.get_Password() << std::endl;
      break;

    case 4: //modificar contraseña
      
      do {
       std::cout << "\nIntroduzca su nueva contraseña (entre 3 y 10 caracteres, un numero, una mayúscula y una minúscula):\n";
      std::cin >> temp;
       contador ++;
       if(contador > 2) {
         contador = 0;
         std::cout<<"La contraseña solo debe y puede contener al menos:"<< 
         "\nUn numero, una mayúscula y una minúscula\n";
       }
      } while (!regex_match (temp, pass_expr));
      data = client.get_email() + " " + temp + " SE";

      for (unsigned travel = 0; travel < data.size(); travel ++) 
      message.text[travel] = data[travel];
      socket_remote.SendTo(message, socket_local_address);    
      message.clear();
      client.set_Password(temp);
      temp.clear();
      std::cout << "\nCambio realizado con exito\n";
      break;

      case 5:
      data = client.get_email() + " " + client.get_Password() + " CL";

      for (unsigned travel = 0; travel < data.size(); travel ++) 
        message.text[travel] = data[travel];
      
      socket_remote.SendTo(message, socket_local_address);    
      message.clear();
      client.Clean();
      break;
    default:
        break;
  }
  
}
catch (std::invalid_argument& error) {
    std::cerr << error.what() << '\n';
  }
  catch (std::system_error& error) {
    std::cerr << error.what() << '\n';
  }
  catch (...) {
    std::cerr << "¡¡¡ ERROR DESCONOCIDO !!!" << '\n';
  }
}

void LoguedActions::ServerClient (int v, int good_port, int dest_good_port, std::string& ip_address) {
 
  try {
    
    // Creamos las estructuras.
    sockaddr_in socket_local_address {};
    sockaddr_in socket_remote_address {};

    MakeIp make;
    // Rellenamos las estructuras.
    socket_local_address = make.make_ip_address (good_port, "127.0.0.1");
    socket_remote_address = make.make_ip_address (0, ip_address);

    // Creamos el socket.
    Socket socket_local (socket_local_address);

    // Creamos la estructura que va a almacenar el mensaje.
    Message message {};
    // Creamos la estructura que va a leer del fichero.

    std::string users_file {"Users.txt"};
    std::string products_file {"productos.txt"};

    // Abrimos el archivo para leer.
    File file (users_file, O_RDWR, -1);
    File product_catalog (products_file, O_RDWR, -1);
    
    socket_local.ReceiveFrom(message, socket_remote_address);

    if( v == 4) {
    // Hasta que no terminemos de leer de memoria.
        file.ChangePasswd(message.text);
        // Si la cuenta ya estaba 1 y sino 0.
        message.clear();
        file.~File();
    }
    if (v == 5) {

      file.DeleteAccount(message.text);

        message.clear();
        file.~File();
    }


    else {

    }
        
    
  }
  catch (std::invalid_argument& error) {
    std::cerr << error.what() << '\n';
  }
  catch (std::system_error& error) {
    std::cerr << error.what() << '\n';
  }
  catch (...) {
    std::cerr << "¡¡¡ ERROR DESCONOCIDO !!!" << '\n';
  }
}

void LoguedActions::ServerBender (int v, int good_port, int dest_good_port, std::string& ip_address) {
 
  try {
    
    // Creamos las estructuras.
    sockaddr_in socket_local_address {};
    sockaddr_in socket_remote_address {};

    MakeIp make;
    // Rellenamos las estructuras.
    socket_local_address = make.make_ip_address (good_port, "127.0.0.1");
    socket_remote_address = make.make_ip_address (0, ip_address);

    // Creamos el socket.
    Socket socket_local (socket_local_address);

    // Creamos la estructura que va a almacenar el mensaje.
    Message message {};
    // Creamos la estructura que va a leer del fichero.

    std::string users_file {"Users.txt"};
    std::string products_file {"productos.txt"};

    // Abrimos el archivo para leer.
    File file (users_file, O_RDWR, -1);
    File product_catalog (products_file, O_RDWR, 0);
    
    socket_local.ReceiveFrom(message, socket_remote_address);

    if(v == 2) {
      int cont = 0;
      std::string product_string;
      for (; message.text[cont] != '\0'; cont++) {
        product_string = product_string + message.text[cont];
      }
      product_string = product_string + " 1";
      cont += 2;
      std::string size = product_catalog.getSize();
      product_catalog.~File();
      File product_catalog (products_file, O_RDWR, -1);
      if(!product_catalog.CheckUploadProduct(message.text)) { 
        product_catalog.~File();
        File product_catalog (products_file, O_RDWR, stoi(size) + 1 + cont);    
        for (unsigned travel = 0; travel < product_string.size(); travel ++) 
          message.text[travel] = product_string[travel];
        product_catalog.WriteEnd(message.text);
      } else {
        product_catalog.UploadExistentProduct(message.text);
      }
      message.clear();
      product_catalog.~File();
      file.~File();
    }

    if( v == 4) {
    // Hasta que no terminemos de leer de memoria.
        file.ChangePasswd(message.text);
        // Si la cuenta ya estaba 1 y sino 0.
        message.clear();
        file.~File();
        product_catalog.~File();
    }
    if (v == 5) {

      file.DeleteAccount(message.text);

      message.clear();
      file.~File();
      product_catalog.~File();
    }

    else {

    }
        
    
  }
  catch (std::invalid_argument& error) {
    std::cerr << error.what() << '\n';
  }
  catch (std::system_error& error) {
    std::cerr << error.what() << '\n';
  }
  catch (...) {
    std::cerr << "¡¡¡ ERROR DESCONOCIDO !!!" << '\n';
  }
}

std::string 
ReturnEmail(std::array<char, 1024>& text) {

  std::string aux;
  for (int i = 0; i < 1023 && text[i] != '\0'; i++){
    if (text[i] != ' ') aux.push_back(text[i]);
    else                break;
  }
  return aux;
}