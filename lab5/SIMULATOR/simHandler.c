//
// Created by stran on 2023-04-09.
//

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include "gui.h"
#include "simHandler.h"
#include <semaphore.h>

pthread_mutex_t simMutex;
pthread_mutex_t fileMutex;

sem_t arrivalSem;
sem_t bridgeEnterSem;

int running;
int fd;
struct termios tty;
uint64_t queues[3];
uint8_t lights;
void initSimHandler(void){
    sem_init(&arrivalSem, 0, 0);
    sem_init(&bridgeEnterSem, 0, 0);

    fd = open("/dev/ttyS2",  O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd==-1) {printf("Couldn't open specified file");}
    tcgetattr(fd, &tty);

    //Set port speed
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag &= ~CSIZE;              // Clear char size
    tty.c_cflag |= CS8;                 // Set 8 bit char size
    tty.c_cflag &= ~PARENB;             // no parity
    tty.c_cflag &= ~CSTOPB;             // 1 stop bit
    tty.c_cflag |= CREAD;    // Enable receive
    running = 1;
    lights = red;
}

void inputHandler(void){
    // Handles the keyboard presses

    char input = getchar();
    // Add car to northQueue
    if (input == 'n') {
        pthread_mutex_lock(&simMutex);
        queues[0]++;
        uint8_t out = 0b0001;
        write(fd, &out, 1);
        pthread_mutex_unlock(&simMutex);
        printStatus();
    }
    // Add car to southQueue
    if (input == 's') {
        pthread_mutex_lock(&simMutex);
        queues[1]++;
        uint8_t out = 0b0100;
        write(fd, &out, 1);
        pthread_mutex_unlock(&simMutex);
        printStatus();
    }
    // Exit simulator
    if (input == 'e') {
        pthread_mutex_lock(&simMutex);
        printf("You have exited the simulation\n");
        running = 0;
        pthread_mutex_unlock(&simMutex);
    }

}

void bridgeHandler(void){
    // Depending on traffic light status ( nGreen, sGreen) it will add a car
    // onto the bridge, let it pass and then remove it.
    pthread_mutex_lock(&simMutex);
    if (queues[lights] == 0 || queues[lights] == 1 ) {
        queues[lights]--;
        queues[2]++;

        //wait for car to pass over bridge
        sleep(5);

        //Remove car from bridge
        queues[2]--;
    }
    pthread_mutex_unlock(&simMutex);

}

void lightHandler(void) {
    uint8_t data = 0;
    while (1)
    {
        data = 0;

        //Read sent value to data
        pthread_mutex_lock(&fileMutex);
        read(fd, &data, 1);
        pthread_mutex_unlock(&fileMutex);

        if(data == 0b0110) { // SouthQueue green
            pthread_mutex_lock(&simMutex);
            lights = southGreen;
            lights = southGreen;
            pthread_mutex_unlock(&simMutex);
        }
        if(data == 0b1001) { // NorthQueue green
            pthread_mutex_lock(&simMutex);
            lights = northGreen;
            pthread_mutex_unlock(&simMutex);
        }
        else {
            pthread_mutex_lock(&simMutex);
            lights = red;
            pthread_mutex_unlock(&simMutex);
        }
    }
}