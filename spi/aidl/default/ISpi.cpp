#define LOG_TAG "SPI_DRIVER"

#include <utils/Log.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "Spi.h"

using namespace aidl::android::hardware::rpi;

namespace aidl {
namespace android {
namespace hardware {
namespace rpi {
namespace spi {

int fd = 0;
typedef struct
{
    int mode;
    int speed;
    int bits;
}spi_driver;

spi_driver spi_dcb;

int32_t spi_open(const char * path)
{
    int32_t fd = -1;

    if (path!= NULL)
    {
        fd = open(path, O_RDWR);
        if (fd < 0)
        {
            ALOGD("open spi device error\n");
            return -1;
        }
    }
    return fd;
}


ndk::ScopedAStatus connect(const std::string& in_port, int32_t in_speed, int32_t in_bits, int32_t in_mode , bool* _aidl_return){
    fd = spi_open(device);
    memset(&spi_dcb, 0x0, sizeof(spi_dcb));
    spi_dcb.mode = in_mode;
    spi_dcb.bits = in_bits;
    spi_dcb.speed = in_speed;
    spi_config(fd, &spi_dcb);

    if(fd < 0){
        *_aidl_return =  false;
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    else {
        *_aidl_return =  true;
        return ndk::ScopedAStatus::ok();
    }
}

ndk::ScopedAStatus disconnect(bool* _aidl_return){
    close(fd);
    *_aidl_return  = true;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus sendByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return) {
    int ret;

    if (out_data->size() < static_cast<size_t>(in_len)) {
        return ndk::ScopedAStatus::fromServiceSpecificError(-2); 
    }

    struct spi_ioc_transfer spi_data;
    memset(&spi_data, 0, sizeof(spi_data));
    spi_data.tx_buf = (unsigned long)out_data->data();
    spi_data.rx_buf = (unsigned long)NULL;
    spi_data.len = in_len;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_data);

   *_aidl_return = ret;

    if (ret < 0) {
        ALOGE("Error sending SPI");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    } else if (ret != in_len) {
        out_data->resize(ret);
    }

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus readByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return) {
    int ret;

    if (out_data->size() < static_cast<size_t>(in_len)) {
        return ndk::ScopedAStatus::fromServiceSpecificError(-2); 
    }

    struct spi_ioc_transfer spi_data;
    memset(&spi_data, 0, sizeof(spi_data));
    spi_data.rx_buf = (unsigned long)out_data->data();
    spi_data.tx_buf = (unsigned long)NULL;
    spi_data.len = in_len;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_data);

    *_aidl_return = ret;

    if (ret < 0) {
        ALOGE("Error reading SPI");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    } else if (ret != in_len) {
        out_data->resize(ret);
    }

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus transferByte(const std::vector<uint8_t>& in_tx, std::vector<uint8_t>* out_rx, int32_t in_len, int8_t* _aidl_return) {
    int ret;

    struct spi_ioc_transfer spi_data;
    memset(&spi_data, 0, sizeof(spi_data));
    spi_data.rx_buf = (unsigned long)out_rx->data();
    spi_data.tx_buf = (unsigned long)in_tx->data();
    spi_data.len = in_len;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_data);

   
    *_aidl_return = ret;

    if (ret < 0) {
        ALOGE("Error transfer SPI");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    } else if (ret != in_len) {
        out_data->resize(ret);
    }

    return ndk::ScopedAStatus::ok();
}


}  // namespace spi
}  // namespace rpi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
