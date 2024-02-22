//
// Created by stran on 2023-04-11.
//

#ifndef SIMULATOR_SIMHANDLER_H
#define SIMULATOR_SIMHANDLER_H
#include <stdint.h>
#include <semaphore.h>
#include <pthread.h>
#include <termios.h>
#include "gui.h"


//Define bridge statuses
#define northGreen 0
#define southGreen 0
#define northRed 1
#define southRed 1



// Declare mutexes as extern
extern pthread_mutex_t simMutex;
extern pthread_mutex_t fileMutex;

extern int fd;
extern uint8_t out;
extern uint64_t queues[3];
extern uint8_t northLight;
extern uint8_t southLight;

extern sem_t arrivalSem;
extern sem_t bridgeEnterSem;

extern struct termios tty;

extern int running;

void initSimHandler(void);
void *inputHandler();
void *bridgeHandler();

#endif //SIMULATOR_SIMHANDLER_H
