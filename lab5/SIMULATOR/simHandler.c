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


int fd;
struct termios tty;
uint64_t queues[3];
uint8_t northLight;
uint8_t southLight;
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

    northLight = northGreen;
    southLight = southRed;
}

void *inputHandler(){
    // Handles the keyboard presses
    while (1) {

    char input;
    input = getchar();
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
        printf("You have exited the simulation\n");
        void *ret;
        return ret;
    }
    }
}

void *bridgeHandler(){
    // Depending on traffic light status ( nGreen, sGreen) it will add a car
    // onto the bridge, let it pass and then remove it.
    if (northLight == northGreen) {
        pthread_mutex_lock(&simMutex);
        queues[0]--;
        queues[2]++;
        printf("Adding car to bridge | NORTH\n");
        printStatus();
        //wait for car to pass over bridge
        sleep(5);

        //Remove car from bridge
        printf("Removing car from bridge | NORTH\n");
        queues[2]--;
        printStatus();
        pthread_mutex_unlock(&simMutex);
    }
    
    else if ( southLight == southGreen) {
        
        pthread_mutex_lock(&simMutex);
        queues[1]--;
        queues[2]++;
        //wait for car to pass over bridge
        printf("Adding car to bridge | SOUTH\n");
        printStatus();
        sleep(5);

        //Remove car from bridge
        printf("Removing car from bridge | SOUTH\n");
        queues[2]--;
        printStatus();
        pthread_mutex_unlock(&simMutex);
    }


}


void bridge() {
    // Create a thread for the bridgeHandler
    pthread_t bridgeThread;
    pthread_create(&bridgeThread, NULL, &bridgeHandler, NULL);
}

void *lightHandler() {
    uint8_t data = 0;
    while (1)
    {
        data = 0;

        //Read sent value to data
        pthread_mutex_lock(&fileMutex);
        read(fd, &data, 1);
        pthread_mutex_unlock(&fileMutex);

        if(data == 0b0100) { // SouthQueue green
            pthread_mutex_lock(&simMutex);
            southLight = southGreen;
            northLight = northRed;
            int data = 0b1000;
            write(fd, &data, 1);
            bridge();
            pthread_mutex_unlock(&simMutex);
        }
        else if(data == 0b0001) { // NorthQueue green
            pthread_mutex_lock(&simMutex);
            northLight = northGreen;
            southLight = southRed;
            int data = 0b0010;
            write(fd, &data, 1);
            bridge();
            pthread_mutex_unlock(&simMutex);
        }
        else if(data == 0b0010) { // NorthQueue red
            northLight = northRed;
        }
        else if(data == 0b1000) { // SouthQueue red
            southLight = southRed;
        }


    }
}