#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
using namespace std;
#define SOCK_PORT 9900
#define BUFFER_SIZE 1024

const string server_ip = "127.0.0.1";

int main(){
    int sock_cli;
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd;

    sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SOCK_PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock_cli, (const sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        cout << "connect fail" << endl;
        exit(1);
    }

    cout << "connect established" << endl;

    while(1){
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        maxfd = 0;
        FD_SET(sock_cli, &rfds);
        if (maxfd < sock_cli) maxfd = sock_cli;

        tv.tv_sec = 5;
        tv.tv_usec = 0;

        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if (retval == -1){
            cout << "select fail" << endl;
            exit(1);
        }else if (retval == 0){
            cout << "No message" << endl;
            continue;
        }else{

            if (FD_ISSET(sock_cli, &rfds)){
                char recvbuf[BUFFER_SIZE];
                int len = recv(sock_cli, recvbuf, sizeof(recvbuf), 0);
                printf("receive message of %s" , recvbuf);
                memset(recvbuf, 0, sizeof(recvbuf));
            }

            if (FD_ISSET(0, &rfds)){
                char sendbuf[BUFFER_SIZE];
                fgets(sendbuf, sizeof(sendbuf), stdin);
                send(sock_cli, sendbuf, strlen(sendbuf), 0);
                memset(sendbuf, 0, sizeof(sendbuf));
            }

        }
    }



}
