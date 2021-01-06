/*
 * @Description: 
 * @FilePath: /example/src/HelloWorldStubImpl.cpp
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-06 10:37:03
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-06 10:37:14
 */
#include "HelloWorldStubImpl.hpp"

HelloWorldStubImpl::HelloWorldStubImpl() { }
HelloWorldStubImpl::~HelloWorldStubImpl() { }

void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
	std::string _name, sayHelloReply_t _reply) {
	    std::stringstream messageStream;
	    messageStream << "Hello " << _name << "!";
	    std::cout << "sayHello('" << _name << "'): '" << messageStream.str() << "'\n";

    _reply(messageStream.str());
};