/*
 * @Description: 
 * @FilePath: /example/src/M4AgentClient.cpp
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-06 10:35:47
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-07 14:43:46
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/nio_m4_agent/M4AgentProxy.hpp>

using namespace v1_0::commonapi::nio_m4_agent;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<M4AgentProxy<>> myProxy =
    	runtime->buildProxy<M4AgentProxy>("local", "m4_agent");

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    std::string returnMessage;
    myProxy->M4Transfer("Bob", callStatus, returnMessage);
    std::cout << "Got message: '" << returnMessage << "'\n";
    return 0;
}
