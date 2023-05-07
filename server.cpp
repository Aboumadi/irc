#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <sys/_endian.h>
#include <sys/_types/_socklen_t.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    //1 : creat a sockett for server

    int server_socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_id != -1)
    {
        printf("server socket created with id %d\n", server_socket_id);
    }
    else
    {
        printf("serevr socket cannot created and the id is %d\n", server_socket_id);
        exit(1);
    }
    //2 : bind the socket to a specific port number

    struct sockaddr_in server_add;
    memset(&server_add, 0, sizeof(server_add));
    server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_add.sin_port = htons(4444);
    if (bind(server_socket_id, (struct sockaddr*)&server_add, sizeof(server_add)) == 0)
        printf("server is binding to a port 4444\n");
    else
    {
        printf("binding failed\n");
        exit (1);
    }
    //3 : listen to an client
    if (listen(server_socket_id, 1) == 0)
        printf("server is listning......\n");
    else
    {
        printf("server cannot listen\n");
        exit (1);
    }

    //4 : accept connection to clinet and return an socket client

    struct sockaddr_in client_add;
    memset(&client_add, 0, sizeof(client_add));
    // socklen_t add_lengh = sizeof(client_add);
    int clientAddrLen = 0;
    int connect_server_sock = accept(server_socket_id, (struct sockaddr*)&client_add, (socklen_t*)&clientAddrLen);
    // printf("here %d\n", connect_server_sock);
    if (connect_server_sock == -1)
    {
        printf("connction not accepted\n");
        exit(1);
    }
    else
    {
        printf("conncetion was accepted with id %d\n", connect_server_sock);
        // printf("connction not acceptd\n");
        // exit(1);
    }
    //5 : send or recieve data from client

    char msg_rcv[1024];
    memset(&msg_rcv, 0, sizeof(msg_rcv));
    recv(connect_server_sock, msg_rcv, 1024, 0);
    //6 : close the socket

    close(server_socket_id);
    close(connect_server_sock);

}