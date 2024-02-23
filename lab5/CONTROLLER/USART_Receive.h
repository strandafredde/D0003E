//
// Created by Justin Gavrell on 2023-04-08.
//

#ifndef LAB5_USART_RECEIVE_H
#define LAB5_USART_RECEIVE_H
#include "trafficLights.h"

typedef struct{
    Object super;
	Bridge *b;
} USART_Receive;

#define USART_ReceiveInit(b) {initObject(), b};

uint8_t USART_Receive2();
void USART_Transmit(unsigned char data);

#endif //LAB5_USART_RECEIVE_H
