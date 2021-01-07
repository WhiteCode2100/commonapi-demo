/*
 * @Description: 
 * @FilePath: /example/src/M4AgentClient.cpp
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-06 10:35:47
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-07 18:50:08
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/nio_m4_agent/M4AgentProxy.hpp>
#include <tigerLogger.h>

using namespace v1_0::commonapi::nio_m4_agent;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<M4AgentProxy<>> myProxy =runtime->buildProxy<M4AgentProxy>("local", "m4_agent");

    LOG_INFO << "Checking availability!";
    while (!myProxy->isAvailable())
        usleep(10);
    LOG_INFO << "Available...";

    CommonAPI::CallStatus callStatus;
    CommonAPI::ByteBuffer inputMsg;
    inputMsg.push_back(0x35);
    inputMsg.push_back(0x36);
    CommonAPI::ByteBuffer returnMessage;
    myProxy->M4Transfer(inputMsg, callStatus, returnMessage);
    
    for (auto i : returnMessage)
        printf("\\x%.2x", i);
    return 0;
}
