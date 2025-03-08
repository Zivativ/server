#include "socket.h"





void SetupSocketList(SocketList* list, int size){
    list->socket = (tcp_socket*)calloc(size, sizeof(tcp_socket));
    list->size = 0;
    list->capacity = size;
}

void InsertSocket(SocketList* list, tcp_socket socket){
    if(list->size == list->capacity){
        printf("Resizing..\n");
        list->capacity *= 2;
        list->socket = (tcp_socket*)realloc(list->socket, list->capacity * sizeof(tcp_socket));
    }
    list->socket[list->size++] = socket;
}

void FreeSocketList(SocketList* list){
    free(list->socket);
    list->capacity = 0;
    list->size = 0;
}
