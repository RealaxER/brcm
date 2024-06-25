#define LOG_TAG "UART_DRIVER"

#include <utils/Log.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include "Uart.h"

using namespace aidl::android::hardware::imx;

namespace aidl {
namespace android {
namespace hardware {
namespace imx {
namespace uart {

int fd =  0;
struct termios options;

Uart::~Uart() {
    ALOGD("=====END UART======");
}

ndk::ScopedAStatus Uart::connect(const std::string& in_port, int32_t in_baud, bool* _aidl_return)
{
    fd = open(in_port.c_str(), O_RDWR | O_NDELAY | O_NOCTTY);
    if (fd < 0) {
        ALOGE("uartConnect: can not open uart");
        *_aidl_return = false;
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }

    tcgetattr(fd, &options);
    options.c_cflag = in_baud | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    if(fd < 0){
        *_aidl_return = false;
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    else {
        *_aidl_return = true;
        return ndk::ScopedAStatus::ok();
    }
}

//void putChars(in String msg);
ndk::ScopedAStatus Uart::disconnect(bool* _aidl_return)
{
    close(fd);
    *_aidl_return  = true;
    return ndk::ScopedAStatus::ok();
}


ndk::ScopedAStatus Uart::sendByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return) {
    if (out_data->size() < static_cast<size_t>(in_len)) {
        return ndk::ScopedAStatus::fromServiceSpecificError(-2); 
    }

    int8_t ret = write(fd, out_data->data(), in_len);
    *_aidl_return = ret;
    if (ret < 0) {
        ALOGE("Error writing to UART");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    } else {
        return ndk::ScopedAStatus::ok();
    }
}


ndk::ScopedAStatus Uart::readByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return) {
    out_data->clear();
    out_data->resize(in_len);

    int8_t ret = read(fd, out_data->data(), in_len);
    *_aidl_return = ret;

    if (ret < 0) {
        ALOGE("Error reading from UART");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    } else if (ret != in_len) {
        out_data->resize(ret);
    }

    return ndk::ScopedAStatus::ok();
}


}  // namespace uart
}  // namespace imx
}  // namespace hardware
}  // namespace android
}  // namespace aidl
