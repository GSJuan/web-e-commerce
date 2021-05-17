/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de ingeniería del software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#pragma once

#include "message.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <cstring>
#include <string>
#include <system_error>

class File {

  public:
    File ();
    File (const File& A);
    File (const std::string& archive, int flags, int size);
    File (const std::string& archive, int flags, mode_t mode, int size);
    ~File (); 

    void Make (const std::string& archive, int flags, int size);
    void MakeMode (const std::string& archive, int flags, mode_t mode, int size);
    
    std::string getSize();
    std::string getNumberOfSend();
    std::string getArchive();
    bool getEnd ();

    void setNumberOfSend (std::string& number_of_send);
    void setArchive(std::string& archive);

    void WriteArray (std::array<char, 1024>& text);
    void PrintArray (std::array<char, 1024>& text);
    void WriteEnd (std::array<char, 1024>& text);
    void WriteBackupArray (std::array<char, 1024>& text);

    void ChangePasswd(std::array<char, 1024>& text);
    void DeleteAccount(std::array<char, 1024>& text);
    bool CheckUploadProduct(std::array<char, 1024>& text);
    void UploadExistentProduct(std::array<char, 1024>& text);

    const int& getFile () const;
    const int& getActualPosition () const;
    const int& getSize () const;
    char* getMemoryRegion () const;
    const bool& getEnd () const;
    const bool& getRead () const;
    const std::string getArchive() const;

    File operator= (File& A);

  private:
    int file_;
    int actual_position_;
    int size_;
    char* memory_region_;
    bool end_;
    bool read_;
    std::string number_of_send_;
    std::string archive_;
};