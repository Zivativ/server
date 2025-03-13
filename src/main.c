#include "conn.h"
#include "client.h"
#include "exfiles/tinycthread/tinycthread.h"





//#include "exfiles/cthreads/cthreads.h"
ip_address ip;
tcp_socket server;
ConnectionList list;


int main(){
    SetupConnectionsList(&list, 1);
    
    if(netlib_init() < 0){
        fail("netlib_init failed: %s\n", netlib_get_error());
        return -1;
    }
    if(netlib_resolve_host(&ip, NULL, 6942) < 0){
        fail("netlib_resolve_host failed: %s\n", netlib_get_error());
        return -1;
    }
    server = netlib_tcp_open(&ip);
    if(!server){
        fail("netlib_tcp_open failed: %s\n", netlib_get_error());
        return -1;
    }
    info("Server Started\n");
    Data data;
    while(1){
        tcp_socket client = netlib_tcp_accept(server);
        thrd_t thread;
        if(client){
            char username[64] = "user";
            Connection con = {true, client, ""};
            strcpy_s(con.username, 64, username);
            AddConnection(&list, con);
            if(thrd_create(&thread, HandleClient, (void*)&list.con[list.size - 1]) != thrd_success){
                fail("Failed Creating Thread.....\n");
                con.active = false;
            }
            //CreateThread(NULL, 0, HandleClient, (void*)&list.con[list.size - 1], 0, 0); 
        } 

    }
    return 0;
}