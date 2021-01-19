/*
 * @Description: 
 * @FilePath: /m4-agent/inc/M4Interface.h
 * @Version: 1.0
 * @Autor: Guangxing Yang
 * @Date: 2021-01-07 16:28:44
 * @LastEditors: Guangxing Yang
 * @LastEditTime: 2021-01-19 14:52:34
 */

#ifndef _M4_INTERFACE_H_
#define _M4_INTERFACE_H_

int RpmsgInit(void);
int RpmsgRead(uint8_t* buffer, uint32_t size);
int RpmsgWrite(uint8_t* buffer, uint32_t size);

#endif