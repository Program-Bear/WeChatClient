cmake_minimum_required(VERSION 3.9)
project(WeChatClient)

set(CMAKE_CXX_STANDARD 11)

add_executable(WeChatClient main.cpp ack_def.h command_def.h Protocal.h Envolop.cpp)