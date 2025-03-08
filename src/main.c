#include "exfiles/netlib.h"
#include "conn.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
//#include "exfiles/cthreads/cthreads.h"
ip_address ip;
tcp_socket server;
ConnectionList list;


typedef struct _Data {
    int version;
    char data[512];
    bool success;
} Data;

Data data;

DWORD WINAPI HandleClient(void* content){
    Connection* con = (Connection*)content;
    tcp_socket client = con->socket;
    netlib_tcp_accept(client);
    printf("connected!\n");
    while(1){
        int rec = netlib_tcp_recv(client, &data, sizeof(Data));
        if(rec <= 0){
            printf("One Client Disconnected!\n");
            break;
        } 
        //printf("Data Received!\n VERSION = %d - DATA = %s - SUCCESS = %d\n", data.version, data.data, data.success);
        if(data.version != 0){
            Data data = {0, "INCORRECT VERSION", false};
            netlib_tcp_send(client, &data, sizeof(data));
            break;
        }
        netlib_tcp_send(client, &data, sizeof(data));
        for(int i = 0; i < list.size; i++){
            // if(memcmp(&list.con[i], con, sizeof(Connection)) != 0){
            // }
            netlib_tcp_send(list.con[i].socket, &data, sizeof(data));

        }
    }
    con->active = false;
    netlib_tcp_close(client);
    return 0;
}

int main(){
    SetupConnectionsList(&list, 1);
    
    if(netlib_init() < 0){
        printf("netlib_init failed: %s\n", netlib_get_error());
        return -1;
    }
    if(netlib_resolve_host(&ip, NULL, 6942) < 0){
        printf("netlib_resolve_host failed: %s\n", netlib_get_error());
        return -1;
    }
    server = netlib_tcp_open(&ip);
    if(!server){
        printf("netlib_tcp_open failed: %s\n", netlib_get_error());
        return -1;
    }
    printf("Server Started\n");
    Data data;
    while(1){
        tcp_socket client = netlib_tcp_accept(server);
        if(client){
            Connection con = {true, client};
            AddConnection(&list, con);
            CreateThread(NULL, 0, HandleClient, (void*)&list.con[list.size - 1], 0, 0); 
        } 

    }
    return 0;
}