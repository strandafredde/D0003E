//
// Created by stran on 2023-04-11.
//

#ifndef SIMULATOR_SIMHANDLER_H
#define SIMULATOR_SIMHANDLER_H
#include <stdint.h>
#include <pthread.h>
#include <termios.h>
#include "gui.h"


//Define bridge statuses
#define northGreen 0
#define southGreen 1
#define red        2

// Declare mutexes as extern
extern pthread_mutex_t simMutex;
extern pthread_mutex_t fileMutex;

extern int fd;
extern uint8_t out;
extern uint64_t queues[3];
extern uint8_t lights;

extern sem_t arrivalSem;
extern sem_t bridgeEnterSem;

extern struct termios tty;

extern int running;

void initSimHandler(void);
void inputHandler(void);
void bridgeHandler(void);

#endif //SIMULATOR_SIMHANDLER_H
