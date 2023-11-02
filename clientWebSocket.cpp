#include "clientWebSocket.hpp"

#include "arguments.hpp"

class WebSocket {
 public:
  WebSocket(std::vector<std::vector<unsigned char>> *VecBuf,
            pthread_mutex_t *mutex) {
    InitSocket();

    this->buffer = new unsigned char[BUFFER_SIZE];
    RequestDataServer();
    int length = GetDataServer();

    std::vector<unsigned char> arr;
    UCharToVector(buffer, length, arr);

    delete[] buffer;

    pthread_mutex_lock(mutex);
    VecBuf->push_back(arr);
    pthread_mutex_unlock(mutex);
  }
  ~WebSocket() { CloseSocket(); }

 private:
  const int DEFAULT_PORT = 80;
  const char *URL_SERVER = "google.com";
  int client;
  unsigned char *buffer;

  void UCharToVector(unsigned char *buf, int &length,
                     std::vector<unsigned char> &arr) {
    for (int i = 0; i < length; i++) {
      arr.push_back(buf[i]);
    }
  }

  void InitSocket() {
    struct sockaddr_in server_address;
    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) {
      std::cout << "=> Error: establishing socket error.\n";
      exit(-1);
    }

    struct hostent *host = gethostbyname(URL_SERVER);

    int status = inet_pton(AF_INET, inet_ntoa(*(struct in_addr *)host->h_addr),
                           &server_address.sin_addr);

    if (status == 0) {
      std::cout << "=> Error: _src_ does not contain text characters that "
                   "represent a "
                   "valid network address for group address mapping.\n";
      exit(-1);
    }

    if (status == -1) {
      std::cout
          << "=> Error: _af_ does not contain a valid address family value.\n";
      exit(-1);
    }

    status = connect(client,
                     reinterpret_cast<const struct sockaddr *>(&server_address),
                     sizeof(server_address));

    if (status != 0) {
      std::cout
          << "=> Error: Failed to establish a connection to the server.\n";
      exit(-1);
    }
  }

  void RequestDataServer() {
    int status = send(client, buffer, BUFFER_SIZE, 0);
    if (status == -1) {
      std::cout << "=> Error: Error sending request.\n";
      exit(-1);
    }
  }

  int GetDataServer() {
    int length = recv(client, buffer, BUFFER_SIZE, 0);

    if (length < 1) {
      std::cout << "=> Error: Connection lost or otherwise while receiving "
                   "server response.\n";
      exit(-1);
    }

    return length;
  }

  void CloseSocket() {
    int status = close(client);

    if (status == -1) {
      std::cout << "=> Error: Error while closing socket.\n";
      exit(-1);
    }
  }
};

void *launchWebSoket(void *args) {
  auto _args = static_cast<Arguments *>(args);

  while (*(_args->ESC) == false) {
    class WebSocket webSocket {
      _args->VecBuf, _args->mutex
    };
  }

  return 0;
}