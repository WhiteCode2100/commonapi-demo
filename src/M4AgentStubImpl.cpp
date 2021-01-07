/*
 * @Description: 
 * @FilePath: /example/src/M4AgentStubImpl.cpp
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-06 10:37:03
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-07 14:44:37
 */
#include "M4AgentStubImpl.hpp"

M4AgentStubImpl::M4AgentStubImpl() { }
M4AgentStubImpl::~M4AgentStubImpl() { }

void M4AgentStubImpl::M4Transfer(const std::shared_ptr<CommonAPI::ClientId> _client,
	std::string _name, M4TransferReply_t _reply) {
	    std::stringstream messageStream;
	    messageStream << "Hello " << _name << "!";
	    std::cout << "M4Transfer('" << _name << "'): '" << messageStream.str() << "'\n";

    _reply(messageStream.str());
};
