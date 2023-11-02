#include "arguments.hpp"
#include "clientWebSocket.hpp"

void *listenInput(void *args);
void threadJoin(pthread_t &socket_t, pthread_t &listen_t);
void threadCreate(pthread_t &socket_t, pthread_t &listen_t, Arguments *args);
void printVector(Arguments *args);

int main() {
  Arguments args;
  pthread_t socket_t, listen_t;

  threadCreate(socket_t, listen_t, &args);

  for (; *(args.ESC) != true;) {
    pthread_mutex_lock(args.mutex);
    printVector(&args);
    pthread_mutex_unlock(args.mutex);
  }

  printVector(&args);

  threadJoin(socket_t, listen_t);

  return 0;
}

void *listenInput(void *args) {
  char c;
  Arguments *_args = static_cast<Arguments *>(args);
  while (true) {
    std::cin >> c;

    if (c == '\033') {
      *(_args->ESC) = true;
      break;
    }
  }

  return 0;
}

void threadJoin(pthread_t &socket_t, pthread_t &listen_t) {
  int status = pthread_join(socket_t, NULL);
  status += pthread_join(listen_t, NULL);

  if (status != 0) {
    std::cout << "=> Error: Cannot join thread.\n";
    exit(-1);
  }
}

void threadCreate(pthread_t &socket_t, pthread_t &listen_t, Arguments *args) {
  int status = pthread_create(&socket_t, NULL, launchWebSoket, args);
  status += pthread_create(&listen_t, NULL, listenInput, args);

  if (status != 0) {
    std::cout << "=> Error: Cannot create a thread.\n";
    exit(-1);
  }
}

void printVector(Arguments *args) {
  for (; args->VecBuf->empty() != true;) {
    for (auto &it : args->VecBuf[0][0]) {
      std::cout << it;
    }
    std::cout << std::endl;
    args->VecBuf->erase(args->VecBuf->begin());
  }
}