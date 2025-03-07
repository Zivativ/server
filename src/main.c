#include "exheaders/netlib.h"
#include <stdint.h>
#include <stdio.h>


int main(){
    if(netlib_init() < 0){
        printf("netlib_init failed: %s\n", netlib_get_error());
        return -1;
    }
    ip_address ip;
    if(netlib_resolve_host(&ip, NULL, 6942) < 0){
        printf("netlib_resolve_host failed: %s\n", netlib_get_error());
        return -1;
    }
    tcp_socket sock = netlib_tcp_open(&ip);
    if(!sock){
        printf("netlib_tcp_open failed: %s\n", netlib_get_error());
        return -1;
    }
    printf("Server Started\n");
    while(1){
        tcp_socket client = netlib_tcp_accept(sock);
        if(client){
            printf("Connected\n");
            char buffer[UINT16_MAX];
            int received = netlib_tcp_recv(client, buffer, UINT16_MAX);
            if(received > 0){
                buffer[received] = '\0';
                printf("%s\n", buffer);
                netlib_tcp_send(client, "h\n", 1);
            }
            netlib_tcp_close(client);
            printf("disconnected\n");
        }

    }
    return 0;
}