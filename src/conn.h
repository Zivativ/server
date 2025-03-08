#ifndef CONN_H_INCLUDED
#define CONN_H_INCLUDED






#include "exfiles/netlib.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>

typedef struct _Connection {
    bool active;
    tcp_socket socket;
} Connection;
typedef struct _ConnectionList{
    Connection* con;
    int size;
    int capacity;
} ConnectionList;

void SetupConnectionsList(ConnectionList* list, int size);
void AddConnection(ConnectionList* list, Connection connection);
void FreeConnectionList(ConnectionList* list);



#endif