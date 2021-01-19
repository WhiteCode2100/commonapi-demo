/*
 * @Description: M4 RPMSG interface implementation and resource hand over 
 * @FilePath: /m4-agent/src/M4Interface.cpp
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-18 17:04:57
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-19 14:52:43
 */
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <tigerLogger/tigerLogger.h>
#include "M4Interface.h"

const char* RPMSG_PATH ="/dev/ttyRPMSG30";
int fd = 0;

int RpmsgInit(void)
{
    int res = 0;
    
    //open RPMSG
    fd = open (RPMSG_PATH,O_RDWR);
    if(fd < 0)
    {
        LOG_INFO << "failed to open rpmsg device" << std::endl;
        res = -1;
    }

    return res;
}

int RpmsgRead(uint8_t* buffer, uint32_t size)
{
    int res = 0;

    if(fd > 0){
        res = read(fd, buffer, size);
        if(res < 0)
        {
            LOG_INFO << "failed to read rpmsg message" << std::endl;
            res = -1;
        }
    }
    
    return res;
}

int RpmsgWrite(uint8_t* buffer, uint32_t size)
{
    int res = 0;

    if(fd > 0){
        res = write(fd, buffer, size);
        if(res < 0)
        {
            LOG_INFO << "failed to write rpmsg message" << std::endl;
            res = -1;
        }
    }
    
    return res;
}