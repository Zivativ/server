#include "client.h"
#include "conn.h"

Data data;
extern ConnectionList list;

// this is ran in a new thread everytime, be aware
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
        Data send = {0, "h", true};
        sprintf(send.data, "%s - %s", con->username, data.data);
        netlib_tcp_send(client, &send, sizeof(data));
        for(int i = 0; i < list.size; i++){
            netlib_tcp_send(list.con[i].socket, &send, sizeof(send));
        }
    }
    con->active = false;
    netlib_tcp_close(client);
    return 0;
}