/*
 * @Description: 
 * @FilePath: /example/src/M4AgentStubImpl.cpp
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-06 10:37:03
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-11 13:08:50
 */
#include <tigerLogger/tigerLogger.h>
#include "M4AgentStubImpl.hpp"

M4AgentStubImpl::M4AgentStubImpl() { }
M4AgentStubImpl::~M4AgentStubImpl() { }

void M4AgentStubImpl::M4Transfer(const std::shared_ptr<CommonAPI::ClientId> _client, CommonAPI::ByteBuffer _msg, M4TransferReply_t _reply) {
	CommonAPI::ByteBuffer messageStream;
	messageStream.push_back(0x11);
	messageStream.push_back(0x12);

	for (auto i : _msg)
        printf("0x%.2x", i);
    _reply(messageStream);
};
