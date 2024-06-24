#include <uart.h>
#include <string.h>
#include <stdio.h>

int Uart_t::read(void *data, int len) {
    return read(fd, data, len);
}

int Uart_t::send(uint8_t * data, int len) {
	return write(fd, data, len);
}

Uart_t::Uart_t(const char* port){
    fd = open(port, O_RDWR | O_NDELAY | O_NOCTTY);
    if (fd < 0) {
        perror("Error opening serial port");
    }
}

Uart_t::~Uart_t(){
	std::cout <<"----END DATA UART----" << std::endl;
}

int Uart_t::connect(int baud) {
    tcgetattr(this->fd, &this->options);
    this->options.c_cflag = baud | CS8 | CLOCAL | CREAD;
    this->options.c_iflag = IGNPAR;
    this->options.c_oflag = 0;
    this->options.c_lflag = 0;
    tcflush(this->fd, TCIFLUSH);
    tcsetattr(this->fd, TCSANOW, &this->options);

    return 0;
}

int Uart_t::disconnect() {
    close(fd);
}