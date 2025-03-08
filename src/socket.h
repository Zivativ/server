#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED






#include "exfiles/netlib.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>

typedef struct _SocketList{
    tcp_socket* socket;
    int size;
    int capacity;
} SocketList;

void SetupSocketList(SocketList* list, int size);
void InsertSocket(SocketList* list, tcp_socket socket);
void FreeSocketList(SocketList* list);




#endif