#ifndef __MYCAN_H
#define __MYCAN_H

void  MyCAN(void);

void MyCAN_Transmit(uint32_t ID,uint8_t Lenth ,uint16_t *Data);

uint8_t MyCAN_ReceiveFlag(void);

void MyCAN_Receive(uint32_t *ID,uint8_t *Lenth ,uint16_t *Data);

#endif

