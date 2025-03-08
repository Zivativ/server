#include "conn.h"





void SetupConnectionsList(ConnectionList* list, int size){
    list->con = (Connection*)calloc(size, sizeof(Connection));
    list->size = 0;
    list->capacity = size;
}

void AddConnection(ConnectionList* list, Connection connection){
    if(list->size == list->capacity){
        printf("Resizing..\n");
        list->capacity *= 2;
        list->con = (Connection*)realloc(list->con, list->capacity * sizeof(Connection));
    }
    for(int i = 0; i < list->size; i++){
        if(list->con[i].active == false){
            printf("Connection %d Reused\n", i);
            list->con[i] = connection;
            return;
        }
    }
    list->con[list->size++] = connection;
}

void FreeConnectionList(ConnectionList* list){
    free(list->con);
    list->capacity = 0;
    list->size = 0;
}
