//
// Created by stran on 2023-04-09.
//

#include "simHandler.h"
#include  <unistd.h>

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

}

void inputHandler(){
    // Handles the keyboard presses

    char input = getchar();
    // Add car to northQueue
    if (input == 'n') {
        queues[0]++;
        uint8_t out = 0b0001;
        write(fd, &out, 1);
    }
    // Add car to southQueue
    if (input == 's') {
        queues[1]++;
        uint8_t out = 0b0100;
        write(fd, &out, 1);
    }
    // Exit simulator
    if (input == 'e') {
        printf("You have exited the simulation");

    }

}

void bridgeHandler(){
    // Depending on traffic light status ( nGreen, sGreen) it will add a car
    // onto the bridge, let it pass and then remove it.
    if (queues[lights] == 0 || queues[lights] == 1 ) {
        queues[lights]--;
        queues[2]++;

        //wait for car to pass over bridge
        sleep(5);

        //Remove car from bridge
        queues[2]--;
    }

}