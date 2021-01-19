/*
 * @Description: M4Agent client application for test
 * @FilePath: /m4-agent/src/M4AgentClient.cpp
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-06 10:35:47
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-19 14:57:03
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/nio_m4_agent/M4AgentProxy.hpp>
#include <tigerLogger/tigerLogger.h>
#include "M4Interface.h"

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
        printf("0x%.2x\r\n", i);
    return 0;
}
