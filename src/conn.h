#ifndef CONN_H_INCLUDED
#define CONN_H_INCLUDED






#include "superheader.h"

typedef struct _Connection {
    bool active;
    tcp_socket socket;
    char username[64];
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