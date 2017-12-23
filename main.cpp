#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Protocal.h"
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include "ack_def.h"
#include "command_def.h"
using namespace std;
#define SOCK_PORT 9897
#define BUFFER_SIZE 1024

const string server_ip = "127.0.0.1";
const char* log_in = "login\n";
const char* log_out = "logout\n";
const char* sign_up = "sign_up\n";
const char* add = "add\n";
const char* ls = "ls\n";
const char* chat = "chat\n";
const char* send_message = "sendmsg";
const char* send_file = "sendfile";
const char* exit_chat = "exit\n";
const char* receive_message = "recvmsg\n";
const char* receive_file = "receive_file\n";
const char* profile = "profile\n";
const char* sync_friend = "sync\n";

int main(){
    int sock_cli;
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd;
    int sock_id = 4;

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
                if (len == 0){
                    cout << "connection fail" << endl;
                    exit(1);
                }
                printf("receive message of %s" , recvbuf);
                memset(recvbuf, 0, sizeof(recvbuf));
            }

            if (FD_ISSET(0, &rfds)){
                char * buffer = new char[BUFFER_SIZE];
                //memset(buffer,0,sizeof(buffer));

                fgets(buffer, sizeof(buffer), stdin);


                if (strcmp(log_in, buffer) == 0){
                    cout << "Please your name" << endl;
                    //char* name = "weijy2";
                    char* name = new char[BUFFER_SIZE];
                    fgets(name, sizeof(name), stdin);

                    cout << "get name of " << name << " size is " << strlen(name) << endl;
                    Protocal* _login = new Protocal(LOG_IN, -1, sock_id, -1, name, strlen(name));
                    cout << "temp" << endl;
                    cout << "after parse " << _login -> get_data() << endl;

                    char* sendtemp = _login ->send_data();
                    cout << "before send: " << sendtemp+24 << endl;
                    cout << _login ->get_length() << endl;
                    send(sock_cli, sendtemp, _login->get_length() , 0);

                }else{
                    cout << "no match of " << buffer << endl;
                }

                //send(sock_cli, sendbuf, strlen(sendbuf), 0);
                //memset(sendbuf, 0, sizeof(sendbuf));

            }

        }
    }



}
