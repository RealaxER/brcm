#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define device      "/dev/spidev3.0"

typedef struct
{
    int mode;
    int speed;
    int bits;
}spi_driver;


int32_t spi_open(const char * path)
{
    int32_t fd = -1;

    if (path!= NULL)
    {
        fd = open(path, O_RDWR);
        if (fd < 0)
        {
            printf("open spi device error\n");
            return -1;
        }
    }

    return fd;
}

int32_t spi_config(int32_t fd, spi_driver* spi_dcb)
{
    int ret;

    if(NULL == spi_dcb)
        return -1;

    ret = ioctl(fd, SPI_IOC_WR_MODE, &spi_dcb->mode);
    if (ret == -1)
    {
       printf("config spi write mode error \n");
        return ret;
    }
    ret = ioctl(fd, SPI_IOC_RD_MODE, &spi_dcb->mode);
    if (ret == -1)
    {
       printf("config spi read mode error \n");
        return ret;
    }

    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spi_dcb->bits);
    if (ret == -1)
    {
       printf("config spi transfer bits error \n");
        return ret;
    }

}
 

int32_t spi_read(int32_t fd, uint8_t *buf, uint32_t len)
{
    int32_t ret;

    struct spi_ioc_transfer spi_data;
    memset(&spi_data, 0, sizeof(spi_data));
    spi_data.rx_buf = (unsigned long)buf;
    spi_data.tx_buf = (unsigned long)NULL;
    spi_data.len = len;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_data);
    if (ret < 1)
    {
        printf("spi read error\n");
    }

    return ret;
}

int32_t spi_write(int32_t fd, uint8_t *buf, uint32_t len)
{
    int ret;

    struct spi_ioc_transfer spi_data;
    memset(&spi_data, 0, sizeof(spi_data));
    spi_data.tx_buf = (unsigned long)buf;
    spi_data.rx_buf = (unsigned long)NULL;
    spi_data.len = len;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_data);
    if (ret < 1)
    {
        printf("spi write error\n");
    }

    return ret;
}

int32_t spi_write_read(int32_t fd, uint8_t *write_buf, uint8_t *read_buf, uint32_t len)
{
    int ret;

    struct spi_ioc_transfer spi_data;
    memset(&spi_data, 0, sizeof(spi_data));
    spi_data.tx_buf = (unsigned long)write_buf;
    spi_data.rx_buf = (unsigned long)read_buf;
    spi_data.len = len;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_data);
    if (ret < 1)
    {
        printf("error write and read\n");
    }
    return ret;
}

int32_t spi_close(int32_t fd)
{
    int32_t ret = 0;

    if(fd < 0)
    {
        printf("fd is invalid\n");
    }
    ret = close(fd);

    return ret;
}

int main(int argc, char * argv [ ])
{
    int fd = 0;
    int i = 0;
    int ret = 0;
    bool cs_change_flag = 0;
    char spi_path[64] = {0};
    char cs_change_buf[2] = {0};
    uint8_t writebuf[1024] = {'1','2','3'};
    uint8_t readbuf[1024] = {0};
    spi_driver spi_dcb;

    printf("spi test\n");

    setbuf(stdout, NULL);
    fd = spi_open(device);

    if(fd < 0){
        printf("open spi fail\n");
    }

    memset(&spi_dcb, 0x0, sizeof(spi_dcb));
    spi_dcb.mode = 0;
    spi_dcb.bits = 8;
    spi_dcb.speed = 500000;

    spi_config(fd, &spi_dcb);

/* double work mode */
   ret = spi_write_read(fd, writebuf, readbuf, 1024);

    printf("\n");

    spi_close(fd);
}
