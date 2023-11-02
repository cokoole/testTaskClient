#pragma once

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstddef>
#include <iostream>
#include <vector>

#define BUFFER_SIZE 1024

void* launchWebSoket(void* args);