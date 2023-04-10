//
// Created by stran on 2023-04-09.
//

#include "simHandler.h"
#include <unistd.h>
#include <termios.h>
#include "gui.h"

void initSimHandler(){
    port = open("/dev/ttyS2",  O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd==-1) {printf("Couldn't open specified file");}
    tcgetattr(fd, &tty);

    //Set port speed
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag &= ~CSIZE;              // Clear char size
    tty.c_cflag |= CS8;                 // Set 8 bit char size
    tty.c_cflag &= ~PARENB;             // no parity
    tty.c_cflag &= ~CSTOPB;             // 1 stop bit
    serialSettings.c_cflag |= CREAD;    // Enable receive

    lights = RED;
}

void inputHandler(){
    // Handles the keyboard presses

    char input = getchar();
    // Add car to northQueue
    if (input == 'n') {
        pthread_mutex_lock(&simMutex);
        queues[0]++;
        uint8_t out = 0b0001;
        write(fd, &out, 1);
        pthread_mutex_unlock(&simMutex);
    }
    // Add car to southQueue
    if (input == 's') {
        pthread_mutex_lock(&simMutex);
        queues[1]++;
        uint8_t out = 0b0100;
        write(fd, &out, 1);
        pthread_mutex_unlock(&simMutex);
    }
    // Exit simulator
    if (input == 'e') {
        pthread_mutex_lock(&simMutex);
        printf("You have exited the simulation");
        pthread_mutex_unlock(&simMutex);
    }

}

void bridgeHandler(){
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

void lightHandler() {
    uint8_t data = 0;
    while (1)
    {
        data = 0;

        //Read sent value to data
        pthread_mutex_lock(&fileMutex);
        read(tty, &data, 1);
        pthread_mutex_unlock(&fileMutex);

        if(data == 0b0100) { // SouthQueue green
            pthread_mutex_lock(&simMutex);
            lights = southGreen
            pthread_mutex_unlock(&simMutex);
        }
        if(data == 0b0001) { // NorthQueue green
            pthread_mutex_lock(&simMutex);
            lights = northGreenGreen
            pthread_mutex_unlock(&simMutex);
        }
        else {
            pthread_mutex_lock(&simMutex);
            lights = red;
            pthread_mutex_unlock(&simMutex);
        }
    }
}