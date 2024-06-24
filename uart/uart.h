#pragma once 
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>

class Uart_t {
private:
    int fd;
    struct termios options; /* Serial ports setting */
public:
    Uart_t(const char * port);
    int send(uint8_t * data, int len);
    int connect(int baud);
    int Uart_t::read(uint8_t *data,int len);
    int disconnect(void);
    ~Uart_t();	
};