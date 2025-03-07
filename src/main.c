#include "exheaders/netlib.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

ip_address ip;
tcp_socket server;
char list[UINT16_MAX];

DWORD WINAPI Handlee(LPVOID lpThreadParameter){
    tcp_socket client = (tcp_socket)lpThreadParameter;
    printf("Connected\n");
    while(1){
        char buffer[UINT16_MAX];
        int received = netlib_tcp_recv(client, buffer, UINT16_MAX);
        if(received > 0){
            buffer[received] = '\0';
            //printf("%s\n", buffer);
            sprintf(list, "%s;User - %s;", list, buffer);
            printf("%s\n", list);
            netlib_tcp_send(client, list, strlen(list));
        } else return 0;
    }
}

int main(){
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
    while(1){
        tcp_socket client = netlib_tcp_accept(server);
        if(client){
            CreateThread(NULL, 0, Handlee, client, 0, 0);
        } 

    }
    return 0;
}