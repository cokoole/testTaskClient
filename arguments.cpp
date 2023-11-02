#include "arguments.hpp"

Arguments::Arguments() {
  VecBuf = new std::vector<std::vector<unsigned char>>;
  ESC = new bool;
  mutex = new pthread_mutex_t;
  *ESC = false;
}

Arguments::~Arguments() {
  delete VecBuf;
  delete ESC;
  delete mutex;
}
