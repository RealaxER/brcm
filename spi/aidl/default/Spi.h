#pragma once

#include <aidl/android/hardware/rpi/spi/BnSpi.h>

namespace aidl {
namespace android {
namespace hardware {
namespace rpi {
namespace spi {

class Spi : public BnSpi {
    public:
    ndk::ScopedAStatus connect(const std::string& in_port, int32_t in_speed, int32_t in_bits, int32_t in_mode , bool* _aidl_return);
    ndk::ScopedAStatus close(bool* _aidl_return);
    ndk::ScopedAStatus sendByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
    ndk::ScopedAStatus readByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
    ndk::ScopedAStatus transferByte(const std::vector<uint8_t>& in_tx, std::vector<uint8_t>* out_rx, int32_t in_len, int8_t* _aidl_return);
};

}  // namespace spi
}  // namespace rpi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
