/*
 * @Description: 
 * @FilePath: /example/src/M4AgentService.cpp
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-06 10:36:13
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-07 18:41:48
 */
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include <tigerLogger.h>
#include "M4AgentStubImpl.hpp"

int main() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<M4AgentStubImpl> M4AgentService =
    	std::make_shared<M4AgentStubImpl>();
    runtime->registerService("local", "m4_agent", M4AgentService);
    LOG_INFO << "Successfully Registered Service!";

    while (true) {
        LOG_INFO << "Waiting for calls... (Abort with CTRL+C)";
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
    return 0;
 }
