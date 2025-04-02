#include "stm32f10x.h"

void  MyCAN(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_CAN1EN,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    CAN_InitTypeDef CAN_InitStructure;
    CAN_Init(CAN1, &CAN_InitStructure);
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;
    CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_2tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
    CAN_InitStructure.CAN_Prescaler = 48;

    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

}
void MyCAN_Transmit(uint32_t ID,uint8_t Lenth ,uint16_t *Data)
{
    CanTxMsg TxMessage;
    TxMessage.StdId = ID;
    TxMessage.ExtId = ID;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_Id_Standard;
    TxMessage.DLC = Lenth;
    for(uint8_t i = 0; i < Lenth; i++)
    {
        TxMessage.Data[i] = Data[i];  
    }
    uint8_t TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
    uint32_t Timeout = 0;
    while(CAN_TransmitStatus(CAN1, TransmitMailbox) != CAN_TxStatus_Ok)
    {
        Timeout++;
        if(Timeout > 100000)
        {
            break;
        }
    }

}

uint8_t MyCAN_ReceiveFlag(void)
{
    if(CAN_MessagePending(CAN1, CAN_FIFO0) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

void MyCAN_Receive(uint32_t *ID,uint8_t *Lenth ,uint16_t *Data)
{
    uint8_t i;
    CanRxMsg RxMessage;
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
    if (RxMessage.IDE == CAN_Id_Standard)
    {
        *ID = RxMessage.StdId;
    }
    else
    {
        *ID = RxMessage.ExtId;
    }
    if (RxMessage.RTR == CAN_RTR_DATA)
    {
        *Lenth = RxMessage.DLC;
        if( i < *Lenth)
        {
            i++;
            Data[i] = RxMessage.Data[i];
        }
    }
    else
    {
        *Lenth = 0;
    }
    
}
