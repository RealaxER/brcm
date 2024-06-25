#define LOG_TAG "I2C_DRIVER"

#include <utils/Log.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "I2c.h"

using namespace aidl::android::hardware::imx;

namespace aidl {
namespace android {
namespace hardware {
namespace imx {
namespace i2c {

int fd =  0;


I2c::~I2c() {
    ALOGD("=====END I2C======");
}

ndk::ScopedAStatus I2c::connect(const std::string& in_port, bool* _aidl_return)
{

    fd = open(in_port.c_str(), O_RDWR);

    if(fd < 0){
        *_aidl_return = false;
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    else {
        *_aidl_return = true;
        return ndk::ScopedAStatus::ok();
    }
}

/* Set the slave address */
ndk::ScopedAStatus I2c::setSlave(int8_t in_addr, bool* _aidl_return)
{
    int ret = ioctl(fd, I2C_SLAVE, in_addr);
    if(ret < 0){
        *_aidl_return = false;
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    else {
        *_aidl_return = true;
        return ndk::ScopedAStatus::ok();
    }
}


ndk::ScopedAStatus I2c::disconnect(bool* _aidl_return)
{
    close(fd);
    *_aidl_return  = true;
    return ndk::ScopedAStatus::ok();
}


ndk::ScopedAStatus I2c::sendByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return) {
    if (out_data->size() < static_cast<size_t>(in_len)) {
        return ndk::ScopedAStatus::fromServiceSpecificError(-2); 
    }

    int8_t ret = write(fd, out_data->data(), in_len);
    *_aidl_return = ret;
    if (ret < 0) {
        ALOGE("Error writing to I2C");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    } else {
        return ndk::ScopedAStatus::ok();
    }
}



ndk::ScopedAStatus I2c::readByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return) {
    out_data->clear();
    out_data->resize(in_len);

    int8_t ret = read(fd, out_data->data(), in_len);
    *_aidl_return = ret;

    if (ret < 0) {
        ALOGE("Error reading from I2C");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    } else if (ret != in_len) {
        out_data->resize(ret);
    }

    return ndk::ScopedAStatus::ok();
}


}  // namespace i2c
}  // namespace imx
}  // namespace hardware
}  // namespace android
}  // namespace aidl
