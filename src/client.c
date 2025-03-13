#include "client.h"
#include "conn.h"
#include "exfiles/netlib.h"


extern ConnectionList list;

static inline void BroadcastMessageAmongAllClients(Connection* con, Data* data){
    Data send = {0, true, 0, ""};
    sprintf(send.data,"%s - %s", con->username, data->data);
    for(int i = 0; i < list.size; i++){
        netlib_tcp_send(list.con[i].socket, &send, sizeof(send));
    }
}

static inline void BroadcastServerMessage(Connection* con, char* message){
    Data send = {0, true, 0, ""};
    sprintf(send.data, "Server - %s", message);
    for(int i = 0; i < list.size; i++){
        netlib_tcp_send(list.con[i].socket, &send, sizeof(send));
    }
}

static inline void Idle(Connection* con){
    Data send = {0, true, 0, ""};
    for(int i = 0; i < list.size; i++){
        netlib_tcp_send(list.con[i].socket, &send, sizeof(send));
    }
}

static inline void ChangeUsername(Connection* con, Data* data){
    for(int i = 0; i < list.size; i++){
        if(strcmp(data->data, list.con[i].username) == 0){
            Data send = {0, false, 2, ""};
            netlib_tcp_send(con->socket, &send, sizeof(send));
            return;
        }
    }
    Data sender;
    sprintf(con->username, "%.64s", data->data);
    char buffer[512];
    sprintf(buffer, "%s changed their username", con->username);
    BroadcastServerMessage(con, buffer);
}

int HandleClient(void* content){
    Data reciever;
    Connection* con = (Connection*)content;
    tcp_socket client = con->socket;
    netlib_tcp_accept(client);
    info("A Client Connected!\n");
    while(1){
        CONTINUE:
        con = (Connection*)content;
        int rec = netlib_tcp_recv(client, &reciever, sizeof(Data));
        if(rec <= 0){
            info("A Client Disconnected!\n");
            break;
        } 
        if(reciever.version != 0){
            Data data = {0, false, 2, "Incorrect Version"};
            netlib_tcp_send(client, &data, sizeof(data));
            break;
        }
        info("%s POSTED %s", con->username, reciever.data);
        for(int i = 0; i < list.size; i++){
            //netlib_tcp_send(list.con[i].socket, &send, sizeof(send));
            printf("%s -\n", list.con[i].username);
        }
        switch(reciever.type){
            case 1:
                BroadcastMessageAmongAllClients(con, &reciever);
                goto CONTINUE;
            case 3:
                ChangeUsername(con, &reciever);
                goto CONTINUE;
            default:
                Data senderror = {0, false, 2, "Unknown Packet"};
                netlib_tcp_send(client, &senderror, sizeof(senderror));
                info("Unknown Packet, Continuing.....\n");
                goto CONTINUE;
        }
        Idle(con);
    }
    con->active = false;
    netlib_tcp_close(client);
    return 0;
}