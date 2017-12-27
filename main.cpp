#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Protocal.h"
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include "ack_def.h"
#include "command_def.h"
using namespace std;
#define SOCK_PORT 9886
#define BUFFER_SIZE 1024
#define CHUNK_SIZE 1024
#define SPLIT "--------------------"

const string server_ip = "127.0.0.1";
const char* log_in = "login\n";
const char* log_out = "logout\n";
const char* sign_up = "signup\n";
const char* _add = "add\n";
const char* _ls = "ls\n";
const char* _search = "search\n";
const char* _chat = "chat\n";
const char* _send_message = "send\n";
const char* send_file = "sendfile\n";
const char* _exit_chat = "exit\n";
const char* _receive_message = "recvmsg\n";
const char* _receive_file = "recvfile\n";
const char* _profile = "profile\n";
const char* _sync_friend = "sync\n";
const char* _test_file = "testfile\n";
const string file_path = "/Users/victor/SocketDownload/";

int main(){
    int sock_cli;
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd;
    int sock_id;
    bool in_log = false;
    bool in_chat = false;
    bool in_file = false;

    int chat_target = -1;
    char* chat_name = new char[100];


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

        tv.tv_sec = 0.1;
        tv.tv_usec = 0;

        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if (retval == -1){
            cout << "select fail" << endl;
            exit(1);
        }else if (retval == 0){
            //cout << "No message" << endl;
            continue;
        }else{

            if (FD_ISSET(sock_cli, &rfds)){
                char recvbuf[BUFFER_SIZE];
                int len = recv(sock_cli, recvbuf, sizeof(recvbuf), 0);
                if (len == 0){
                    cout << "connection fail" << endl;
                    exit(1);
                }
                //cout << len << endl;
                int* temp = new int();
                memcpy(temp, recvbuf+4, 4);
                int id = *temp;
                //cout << "get id: " << id << endl;

                Protocal* receive_packet = new Protocal(recvbuf);
                //cout << "receive command: " << receive_packet ->get_command() << endl;
                //cout << "receive ack: " << receive_packet -> get_ack() << endl;
                switch(receive_packet ->get_command()){
                    case(CONNECT_ACK):{
                        if (receive_packet -> get_ack() == SUCCESS){
                            cout << "connect successful" << " with socket id: " << receive_packet ->get_source() << endl;
                        }
                        sock_id = receive_packet ->get_source();
                        break;
                    }

                    case(SIGN_UP_ACK):{
                        if (receive_packet ->get_ack() == SUCCESS){
                            cout << "sign up successful" << endl;
                        }
                        else if(receive_packet ->get_ack() == TOO_MANY_CLIENT){
                            cout << "Up to client limit sign up failed" << endl;
                        }
                        else if (receive_packet ->get_ack() == SAME_NAME){
                            cout << "There exists a same user name" << endl;
                        }
                        break;

                    }
                    case(LOG_IN_ACK):{
                        if (receive_packet ->get_ack() == SUCCESS){
                            cout << "Log in successful" << endl;
                            in_log = true;
                        }
                        else if(receive_packet ->get_ack() == BAD_USER){
                            cout << "There does not exists such user" << endl;
                        }
                        else if(receive_packet ->get_ack() == BAD_PASSWORD){
                            cout << "Wrong Password" << endl;
                        }
                        else if(receive_packet ->get_ack() == RE_LOG){
                            cout << "You has already log in" << endl;
                        }
                        break;
                    }

                    case(LOG_OUT_ACK):{
                        if (receive_packet ->get_ack() == SUCCESS){
                            cout << "Log out goodbye" << endl;
                            in_log = false;
                        }else if(receive_packet ->get_ack() == BAD_USER){
                            cout << "There does not exists such user" << endl;
                        }else if(receive_packet ->get_ack() == BAD_LOGOUT){
                            cout << "You has not log in before" << endl;
                        }
                        break;
                    }

                    case(ADD_ACK):{
                        if(receive_packet ->get_ack() == SUCCESS){
                            char* friend_name = receive_packet ->get_data();
                            cout << friend_name << " has become your friend!" << endl;
                        }else if(receive_packet ->get_ack() == BAD_USER){
                            cout << "There does not exists such user" << endl;
                        }else if(receive_packet ->get_ack() == ADD_SELF){
                            cout << "You can't add your self" << endl;
                        }
                        break;

                    }
                    case(LS_ACK):{
                        if(receive_packet ->get_ack() == SUCCESS){
                            cout << "Your friend are as follow" << endl;
                            char* buffer_data = receive_packet ->get_data();
                            char* temp = strtok(buffer_data, "&");
                            while(temp){
                                cout << temp << endl;
                                temp = strtok(NULL, "&");
                            }
                        }else{
                            cout << "List fail" << endl;
                        }
                        break;

                    }
                    case(SEARCH_ACK):{
                        if(receive_packet->get_ack() == SUCCESS){
                            cout << "All people are shown as follow: " << endl;
                            char* buffer_data = receive_packet ->get_data();
                            //cout << buffer_data << endl;
                            char* temp = strtok(buffer_data, "&");
                            while(temp){
                                cout << temp << endl;
                                temp = strtok(NULL, "&");
                            }
                        }else{
                            cout << "Search fail" << endl;
                        }
                        break;

                    }
                    case(CHAT_ACK):{
                        if (receive_packet ->get_ack() == SUCCESS){
                            chat_target = receive_packet ->get_target();
                            char* _chat_name = receive_packet ->get_data();
                            cout << "Start Chatting with " << _chat_name << endl;
                            in_chat = true;
                            chat_name = _chat_name;
                        }else if(receive_packet ->get_ack() == OFF_LINE){
                            cout << "Your friend is off line." << endl;
                            cout << "We will keep the latest message or file for you" << endl;
                            chat_target = receive_packet ->get_target();
                            in_chat = true;
                        }else if(receive_packet ->get_ack() == BAD_USER){
                            cout << "There does not exists such user" << endl;
                        }else if(receive_packet ->get_ack() == NOT_FRIEND){
                            cout << "Your chatting target is not your friend" << endl;
                        }
                        break;

                    }

                    case(NEW_MESSAGE):{
                        cout << "You receive a message: " << receive_packet ->get_data() << endl;
                        break;
                    }

                    case(EXIT_ACK):{
                        if(receive_packet ->get_ack() == SUCCESS){
                            cout << "Exit Chat" << endl;
                            in_chat = false;
                            chat_target = -1;
                        }else{
                            cout << "Exit Fail" << endl;
                        }
                        break;
                    }

                    case(NEW_FILE):{
                        if(receive_packet ->get_ack() == SUCCESS){

                            cout << "You have received a new file named " << receive_packet ->get_data() << endl;
                            cout << "Using recvfile to download"<< endl;
                        }else{
                            cout << "File Receive Fail" << endl;
                        }
                        break;
                    }
                    case(FILE_END_ACK):{
                        if (receive_packet ->get_ack() == SUCCESS){
                            cout << "Successfully Send" << endl;
                        }else{
                            cout << "Send Fail" <<endl;
                        }
                        break;
                    }
                    case(OLD_MESSAGE):{
                        char* buffer = receive_packet ->get_data();
                        if(receive_packet ->get_ack() == SUCCESS){
                            char* msg = strtok(buffer,"&");
                            char* name = strtok(NULL, "&");
                            cout << "When you are off-line " << " your frined " << name << " has sent a message to you" << endl;
                            cout << "The Message is: " << msg << endl;
                        }else{
                            cout << "Old Message get failed" << endl;
                        }
                        break;
                    }

                    case(PROFILE_ACK):{
                        if(receive_packet ->get_ack() == SUCCESS){
                            cout << "Your profile is as follow" << endl;
                            char* buffer_data = receive_packet -> get_data();
                            char* temp = strtok(buffer_data, "&");
                            char* _name = temp;
                            cout << "Your name is: " << _name << endl;
                            temp = strtok(NULL, "&");
                            char* _password = temp;
                            cout << "Your password is: " << _password << endl;
                        }else{
                            cout << "Get Profile fail" << endl;
                        }
                        break;
                    }

                    case(REFILE_ACK):{
                        if(receive_packet ->get_ack() == SUCCESS){
                            if(in_file){
                                break;
                            }
                            in_file = true;
                            string file_name = receive_packet ->get_file_name();
                            int size = receive_packet ->get_target();
                            string path = file_path+file_name;
                            //cout << "path is: " << path << endl;

                            FILE* fp = fopen(path.c_str(),"wb+");
                            if(fp == NULL){
                                cout << "No such file" << endl;
                                break;
                            }
                            char* buffer = new char[BUFFER_SIZE];
                            bzero(buffer, BUFFER_SIZE);
                            int length = recv(sock_cli, buffer, BUFFER_SIZE,0);
                            int temp = 0;
                            do{
                                cout << "Download packet of: " << length << " Bytes" << endl;
                                //cout << length << endl;
                                fwrite(buffer, sizeof(char), length, fp);
                                //if(length < BUFFER_SIZE) break;
                                temp += length;
                                //if(temp == size) break;

                                bzero(buffer, BUFFER_SIZE);
                                if(temp == size) break;

                                length = recv(sock_cli, buffer, BUFFER_SIZE,0);
                                //cout << "next judge: " << length << endl;
                            }while(length > 0);
                            //cout << temp << " " << size << endl;
                            cout << "DownLoad Successful! File saved at " + path << endl;
                            fclose(fp);
                            in_file = false;
                        }else{
                            cout << "Receive File Fail" << endl;
                        }
                        break;
                    }



                }
                memset(recvbuf, 0, sizeof(recvbuf));
               // delete receive_packet;
            }

            if (FD_ISSET(0, &rfds)){
                char * buffer = new char[BUFFER_SIZE];
                //memset(buffer,0,sizeof(buffer));
                size_t size = BUFFER_SIZE;
                //fgets(buffer, sizeof(buffer), stdin);
                getline(&buffer,&size,stdin);
                //cin >> buffer;
                //cout << "get input of " << buffer << endl;
                //cout << strcmp("send_file\n",buffer) << endl;
                //cout << "chat name is: " << chat_name << endl;
                if(strcmp(send_file, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if(!in_chat){
                        cout << "You are not in chat" << endl;
                        continue;
                    }
                    cout << "Please input the path(without space)" << endl;
                    //string now_path = "/Users/victor/Test/Archive.zip";
                    string now_path;
                    cin >> now_path;

                    cout << "Please input the filename(without space)" << endl;
                    //string filename = "Archive.zip";
                    string filename;
                    cin >> filename;

                    string target_name = chat_name;

                    if(access(now_path.c_str(),F_OK) != 0){
                        cout << "Invalid file path: "<< now_path.c_str()  << endl;
                        continue;
                    }

                    //cout << "Send Head of: " << target_name << endl;
                    Protocal* file_start = new Protocal(FILE_START, -1,sock_id, chat_target, "",  filename, target_name, 0);
                    send(sock_cli,file_start ->send_data(),file_start->get_length(),0);
                    cout << "File Transfer Start" << endl;
                    char* chunk = new char[CHUNK_SIZE];
                    int length = 0;
                    bzero(chunk, CHUNK_SIZE);
                    FILE* fp = fopen(now_path.c_str(), "rb");

                    while((length = fread(chunk, sizeof(char), CHUNK_SIZE, fp)) > 0){
                        cout << "Send length of: " << length << endl;
                        //cout << "Send Body" << endl;
                        if(send(sock_cli,chunk,length,0) == -1){
                            cout << "Socket Error" << endl;
                        }

                        bzero(chunk,length);
                    }
                    fclose(fp);
                    cout << "Upload finish" << endl;
                }


                if (strcmp(sign_up, buffer) == 0){
                    if (in_log){
                        cout << "You has already log in" << endl;
                        continue;
                    }
                    if (in_chat){
                        cout << "You are in chat" << endl;
                    }
                    cout << "Please your username(less than 100 no space)" << endl;
                    char* name = new char[100];
                    cin >> name;
                    strtok(name, "\n");

                    cout << "Please your password(less than 100 no space)" << endl;
                    char* password = new char[100];
                    cin >> password;
                    strtok(password, "\n");

                    char* buffer = new char[BUFFER_SIZE];
                    memset(buffer, 0, sizeof(buffer));
                    memcpy(buffer, name, strlen(name));
                    memcpy(buffer+strlen(name), "&", 1);
                    memcpy(buffer+strlen(name) + 1, password, strlen(password));

                    Protocal* _signup = new Protocal(SIGN_UP, -1, sock_id, -1, buffer, strlen(buffer));
                    char* sendtemp = _signup ->send_data();
                    send(sock_cli, sendtemp, _signup ->get_length(),0);
                }

                if (strcmp(log_in, buffer) == 0){
                    if (in_log){
                        cout << "You has already log in" << endl;
                        continue;
                    }
                    if (in_chat){
                        cout << "You are in chat" << endl;
                        continue;
                    }
                    cout << "Please your name" << endl;
                    char* name = new char[100];
                    //fgets(name, sizeof(name), stdin);
                    cin >> name;
                    strtok(name, "\n");

                    cout << "Please your password" << endl;
                    char* password = new char[100];
                    //fgets(password, sizeof(password), stdin);
                    cin >> password;
                    strtok(password, "\n");

                    char* buffer = new char[BUFFER_SIZE];
                    memset(buffer,0,sizeof(buffer));
                    memcpy(buffer, name, strlen(name));
                    memcpy(buffer + strlen(name), "&", 1);
                    memcpy(buffer + strlen(name)+1, password, strlen(password));

                    Protocal* _login = new Protocal(LOG_IN, -1, sock_id, -1, buffer, strlen(buffer));
                    char* sendtemp = _login ->send_data();
                    //cout << "before send: " << sendtemp+24 << endl;
                    send(sock_cli, sendtemp, _login->get_length() , 0);
                  //  delete _login;
                  //  delete name;
                  //  delete password;
                }
                if (strcmp(log_out, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }

                    if(in_chat){
                        cout << "You are in chat" << endl;
                        continue;
                    }

                    Protocal* _logout = new Protocal(LOG_OUT,-1,sock_id,-1,NULL,0);
                    char* sendtemp = _logout ->send_data();
                    send(sock_cli, sendtemp,_logout ->get_length(),0);
                  // delete _logout;
                }
                if(strcmp(_search, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if (in_chat){
                        cout << "You are in chat" << endl;
                        continue;
                    }
                    Protocal* _search = new Protocal(SEARCH,-1,sock_id,-1,NULL,0);
                    char* sendtemp = _search ->send_data();
                    send(sock_cli, sendtemp, _search ->get_length(), 0);
                  //  delete _search;
                }
                if(strcmp(_add, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if (in_chat){
                        cout << "You are in chat" << endl;
                        continue;
                    }
                    cout << "Please input the people you want to add" << endl;
                    char* name = new char[100];
                    //fgets(name, sizeof(name), stdin);
                    cin >> name;
                    name = strtok(name, "\n");

                    Protocal* add_ = new Protocal(ADD, -1, sock_id, -1, name, strlen(name));
                    char* sendtemp = add_ ->send_data();
                    send(sock_cli, sendtemp, add_ ->get_length(), 0);
                   // delete add_;
                   // delete name;
                }
                if (strcmp(_ls, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if(in_chat){
                        cout << "You are in chat" << endl;
                        continue;
                    }
                    Protocal* ls_ = new Protocal(LS, -1, sock_id, -1, NULL, 0);
                    char* sendtemp = ls_ ->send_data();
                    send(sock_cli, sendtemp, ls_ ->get_length(), 0);
                }
                if(strcmp(_chat, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if(in_chat){
                        cout << "You are in chat" << endl;
                        continue;
                    }
                    cout << "Please input your target" <<endl;
                    char* name = new char[100];
                    //fgets(name, sizeof(name), stdin);
                    cin >> name;
                    name = strtok(name, "\n");
                    memcpy(chat_name, name, strlen(name));

                    Protocal* chat_ = new Protocal(CHAT, -1, sock_id, -1, name, strlen(name));
                    char* sendtemp = chat_ ->send_data();
                    send(sock_cli, sendtemp, chat_ ->get_length(), 0);
                }

                if (strcmp(_send_message, buffer)==0){
                    if (!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if (!in_chat){
                        cout << "You are not in chat" << endl;
                        continue;
                    }

                    cout << "Please input your message(less than 1024)" << endl;

                    char* mes = new char[1024];
                    memset(mes,0,sizeof(mes));
                    size_t size = 1024;
                    getline(&mes, &size, stdin);

                    char* temp = strtok(mes, "\n");

                    cout << "Send: " << temp << endl;
                    Protocal* mes_ = new Protocal(MESSAGE, -1, sock_id, chat_target, temp, strlen(temp));
                    send(sock_cli, mes_ ->send_data(),  mes_ ->get_length(), 0);
                }

                if (strcmp(_exit_chat, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if(!in_chat){
                        cout << "You are not in chat" << endl;
                        continue;
                    }
                    Protocal* exit_ = new Protocal(EXIT, -1, sock_id, chat_target, NULL, 0);
                    send(sock_cli, exit_ ->send_data(), exit_ ->get_length(), 0);
                    in_chat = false;
                    chat_name = "";
                }

                if (strcmp(_profile, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if (in_chat){
                        cout << "You are in chat" << endl;
                        continue;
                    }
                    Protocal* profile_ = new Protocal(PROFILE, -1, sock_id, -1, NULL, 0);
                    send(sock_cli, profile_ ->send_data(), profile_ ->get_length(), 0);
                }

                if(strcmp(_sync_friend, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if(in_chat){
                        cout << "You are in chat" << endl;
                        continue;
                    }
                    Protocal* sync_ = new Protocal(SYNC, -1, sock_id, -1, NULL, 0);
                    send(sock_cli, sync_ ->send_data(), sync_ ->get_length(),0);
                }

                if(strcmp(_receive_message, buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    if (in_chat){
                        cout << "You are in chat" << endl;
                        continue;
                    }
                    Protocal* rem = new Protocal(REMESSAGE,-1,sock_id,-1,NULL,0);
                    send(sock_cli, rem ->send_data(), rem ->get_length(), 0);
                }

                if(strcmp(_receive_file,buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }

                    Protocal* ref = new Protocal(REFILE,-1,sock_id,-1,NULL,0);
                    send(sock_cli, ref ->send_data(), ref ->get_length(), 0);

                }
                if(strcmp(_test_file,buffer) == 0){
                    if(!in_log){
                        cout << "You has not log in before" << endl;
                        continue;
                    }
                    Protocal* test = new Protocal(REFILE,-1,sock_id,-1,NULL,0);
                    send(sock_cli,test ->send_data(), test->get_length(),0);
                }

                //delete buffer;
            }
        }
    }



}
