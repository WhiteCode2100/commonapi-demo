/*
 * @Description: 
 * @FilePath: /example/inc/M4AgentStubImpl.hpp
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-06 10:36:38
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-07 13:53:59
 */
#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/nio_m4_agent/M4AgentStubDefault.hpp>

class M4AgentStubImpl: public v1_0::commonapi::nio_m4_agent::M4AgentStubDefault {
public:
    M4AgentStubImpl();
    virtual ~M4AgentStubImpl();
    virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
    	std::string _name, sayHelloReply_t _return);
};
#endif /* HELLOWORLDSTUBIMPL_H_ */
