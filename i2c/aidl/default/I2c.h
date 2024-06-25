#pragma once

#include <aidl/android/hardware/imx/i2c/BnI2c.h>

namespace aidl {
namespace android {
namespace hardware {
namespace imx {
namespace i2c {

class I2c : public BnI2c {
    public:
    virtual ~I2c(); // Virtual destructor
    ndk::ScopedAStatus connect(const std::string& in_port, bool* _aidl_return);
    ndk::ScopedAStatus setSlave(int8_t in_addr, bool* _aidl_return);
    ndk::ScopedAStatus disconnect(bool* _aidl_return);
    ndk::ScopedAStatus sendByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
    ndk::ScopedAStatus readByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
};

}  // namespace i2c
}  // namespace imx
}  // namespace hardware
}  // namespace android
}  // namespace aidl
