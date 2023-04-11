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

void USART_Receive(Bridge *b);

#endif //LAB5_USART_RECEIVE_H
