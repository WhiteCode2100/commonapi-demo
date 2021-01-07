/*
 * @Description: 
 * @FilePath: /example/inc/M4Msg.h
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-07 16:28:44
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-07 17:50:17
 */

#ifndef _M4_MSG_H_
#define _M4_MSG_H_

#include <stdint.h>

struct DataStruct{
    uint16_t m_DataType:8;          //data type
    uint16_t m_DataLength:8;        //frame length
    uint8_t buf[0];                 //raw data
};

struct MsgStruct{
    uint32_t m_Header:8;            //msg header for sync
    uint32_t m_MsgType:8;           //Msg type
    uint32_t m_Length:8;            //data length (bytes)
    uint32_t m_Ack:8;               //seq and ack
    uint16_t m_Option:16;           //Option bit
    struct DataStruct m_Data;       //data payload
    uint32_t m_Parity:16;           //parity bit
    uint32_t m_End:8;               //End bit
};

#endif