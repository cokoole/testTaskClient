#pragma once
#include <pthread.h>

#include <vector>
#define SIZE_BUFFER 1024

class Arguments {
 public:
  pthread_mutex_t* mutex;
  bool* ESC;
  std::vector<std::vector<unsigned char>>* VecBuf;

  Arguments();
  ~Arguments();
};