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
    //1 : creat socket for client

    int client_socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_id != -1)
        printf("socket client was craeted with id : %d\n", client_socket_id);
    else
    {
        printf("socket client not created\n");
        exit(1);
    }
    //2 : connect client to a specific server
    struct sockaddr_in client_addres;
    memset(&client_addres, 0, sizeof(client_addres));
    client_addres.sin_family = AF_INET;
    client_addres.sin_addr.s_addr = inet_addr("localhost");
    client_addres.sin_port = htons(4444);
    if (connect(client_socket_id, (struct sockaddr*)&client_addres, sizeof(client_addres)) != 0)
    {
        printf("conncetion succesfully\n");
    }
    else
    {
        printf("connection was faild\n");
        exit (1);
    }
    //3 : send data to server
    
    char msg[] = "i'm the first one\n";
    send(client_socket_id, msg, strlen(msg), 0);
    close(client_socket_id);
    printf("client socket was closed\n");
    //3 : receive data from server
}