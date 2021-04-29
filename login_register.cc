/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#include "login_register.h"

void
LoginRegister::HowUse () {

  std::string read;
  value = -1;
  do {
    std::cout << "Introduzca:\n1. Para hacer LOGIN como cliente\n2. Para hacer" 
              << " LOGIN como vendedor\n3. Para REGISTRARTE como cliente\n4. "
              << "Para REGISTRARTE como vendedor\n5. Para salir\n";
    std::cin >> read;
    if (std::isdigit(read[0]))
      value = read[0] - '0';
    read.clear();

  } while (value < 1 || value > 5);

}



int
LoginRegister::get_Value() {

  return value;
}



void 
LoginRegister::LoginReg (int v, int good_port, int dest_good_port,
                      std::string& ip_address) {

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

    std::string email, pass, data;

    // Leemos de teclado.
    std::cout << "Introduza su email:\n";
    std::cin >> email;
    std::cout << "Introduza su contraseña:\n";
    std::cin >> pass;

    // Diferenciamos entre login/Registro del cliente y del vendedor.
    if (v == 1 || v == 3)
      data = email + " " + pass + " CL";
    else 
      data = email + " " + pass + " SE";

    // Guardamos los datos en la estructura.
    for (unsigned travel = 0; travel < data.size(); travel ++) 
      message.text[travel] = data[travel];

    
    // Enviamos el mensaje y limpiamos nuestra estructura.
    socket_remote.SendTo(message, socket_local_address);    
    message.clear();

    // Esperamos la confirmación del servidor.
    socket_remote.ReceiveFrom(message, socket_local_address);
    
    // Si envía un 1, la cuenta existe y en el caso del login los datos coinciden
    // y en el caso del registro el email ya existe.
    if (message.text[0] == '1') {
      if (v <= 2) { 
        std::cout << "\n\n\nLogin exitoso\n\n\n\n\n\n";
        client.set_Email(email);
        client.set_Password(pass);
        client.exito = true;
      }
      else
        std::cout << "\n\n\nError de Registro, ya hay un usuario con ese email\n\n\n\n\n\n";
    }

    // Si envía un 0, la cuenta no existe, entonces se pudo crear en el caso 
    // del registro y en el caso del login no se encontró la cuenta o la
    // contraseña es erronea.
    else if (message.text[0] == '0') {
      if (v <= 2)
        std::cout << "\n\n\nError de Login, datos Erroneos\n\n\n\n\n\n";
      else {
        std::cout << "\n\n\nRegistro exitoso\n\n\n\n\n\n\n";
        client.set_Email(email);
        client.set_Password(pass);
        client.exito = true;
      }
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



void 
LoginRegister::ServerLoginReg (int v, int good_port, int dest_good_port, std::string&
                            ip_address) {
  
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
    Message text {};
    std::string read_file {"Users.txt"};

    // Abrimos el archivo para leer.
    File file (read_file, 0000, 0);

    
    socket_local.ReceiveFrom(message, socket_remote_address);
    

    int counter = 0;
    bool equal{true};
    bool end{false};

    // Hasta que no terminemos de leer de memoria.
    while(!file.getEnd()) {
      
      // Leemos del archivo mapeado en memoria.
      file.WriteArray(text.text);
      // Si queremos hacer login miramos que la cuenta sea de vendedor o de 
      // cliente, miramos la contraseña y el email.
      if (v <= 2) {
        while (message.text[counter] != '\0' || text.text[counter] != '\0') {
          if (message.text[counter] != text.text[counter])
            equal = false;
            counter ++;
        }
        counter = 0;
      }
      // Si queremos registrarnos solo tenemos que mirar que el email no este
      // en uso.
      else {
        if (ReturnEmail(text.text) != ReturnEmail(message.text))
          equal = false;
      }

      if (equal) {
        end = true;
        break;
      }
      equal = true;
      text.clear();
    }
  
    // Si la cuenta ya estaba 1 y sino 0.
    text.clear();
    if (end)
      text.text[0] = '1';
    else
      text.text[0] = '0';

    // Para registrarnos, tenemos que abrir el archivo en memoria y reservar
    // más espacio, para averiguamos el tamaño de lo que queremos añadir y el
    // tamaño del archivo previamente.
    if (!end && v >= 3){
      
      int cont;
      for (; message.text[cont] != '\0'; cont++);

      std::string size = file.getSize();
      // Cerramos el archivo que solo se abrió para lectura.
      file.~File();

      // volvemos a abrir el archivo para lecritura y lectura.
      File file (read_file, O_RDWR, stoi(size) + 1 + cont);

      // Escribimos al final.
      file.WriteEnd(message.text);
    }
    socket_local.SendTo(text, socket_remote_address);
    
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
LoginRegister::ReturnEmail(std::array<char, 1024>& text) {

  std::string aux;
  for (int i = 0; i < 1023 && text[i] != '\0'; i++){
    if (text[i] != ' ') aux.push_back(text[i]);
    else                break;
  }
  return aux;
}