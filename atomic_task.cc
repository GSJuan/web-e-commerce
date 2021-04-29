/* Univerdidad: Universidad de La Laguna.
   Grado:       Grado de ingeniería informática.
   Asignatura:  Fundamentos de Ingeniería del Software
   Proyecto:    e-commerce
   Compilar:    g++ -g -pthread -o Netcp file.cc netcp.cc socket.cc atomic_task.cc login_register.cc client.cc make_ip.cc
   Ejecutar:    ./Netcp
*/

#include "atomic_task.h"

AtomicTask::AtomicTask () {

  mutex.lock();
  end_send_ = false;
  pause_ = false;
  quit_app_send_ = 0;
  mutex.unlock();
}



AtomicTask::AtomicTask (const AtomicTask& A) {

  mutex.lock();
  bool end_send = A.getEndSend();
  end_send_ = end_send;
  bool pause = A.getPause();
  pause_ = pause;
  int quit_app_send = A.getQuitAppSend();
  quit_app_send_ = quit_app_send;
  mutex.unlock();
}



AtomicTask::~AtomicTask() {}



void 
AtomicTask::setQuitAppSend (int value) {

  mutex.lock();
  quit_app_send_ = value;
  mutex.unlock();
}



const std::atomic_int& 
AtomicTask::getQuitAppSend () const {

  return quit_app_send_;
}



std::atomic_int& 
AtomicTask::getQuitAppSend () {

  return quit_app_send_;
}



void 
AtomicTask::setEndSend (bool value) {

  mutex.lock();
  end_send_ = value;
  mutex.unlock();
}



const std::atomic_bool& 
AtomicTask::getEndSend () const {

  return end_send_;
}



std::atomic_bool& 
AtomicTask::getEndSend () {

  return end_send_;
}



void 
AtomicTask::setPause (bool value) {

  mutex.lock();
  pause_ = value;
  mutex.unlock();
}



const std::atomic_bool& 
AtomicTask::getPause () const {

  return pause_;
}



std::atomic_bool& 
AtomicTask::getPause () {

  return pause_;
}



AtomicTask
AtomicTask::operator= (AtomicTask& A) {

  AtomicTask copy(A);
  return copy;
}



bool
AtomicTask::operator== (AtomicTask& A) {

  return (end_send_ == A.getEndSend() && pause_ == A.getPause() && quit_app_send_ == A.getQuitAppSend());
}
