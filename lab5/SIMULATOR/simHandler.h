//
// Created by stran on 2023-04-09.
//


#ifndef LAB5_SIMHANDLER_H
#define LAB5_SIMHANDLER_H

#include <stdint.h>
#include <pthread.h>
#include <termios.h>


//Define bridge statuses
#define northGreen 0
#define southGreen 1
#define red        2

pthread_mutex_t simMutex;
pthread_mutex_t fileMutex;

int port;
uint8_t out;
uint64_t queues[3];
uint8_t lights;

struct termios tty;

void initSimHandler();
void inputHandler():
void bridgeHandler();

#endif //LAB5_SIMHANDLER_H
