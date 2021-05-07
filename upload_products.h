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

class UploadProducts {
 public:
  UploadProducts(Client& client) {client_ = client};
  void Menu();
  int get_value(){return value;}
 private:
  int value {-1};
  Client& client_;
};