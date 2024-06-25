#pragma once

#include <aidl/android/hardware/imx/spi/BnSpi.h>

namespace aidl {
namespace android {
namespace hardware {
namespace imx {
namespace spi {

class Spi : public BnSpi {
    public:
    virtual ~Spi(); // Virtual destructor
    ndk::ScopedAStatus connect(const std::string& in_port, int32_t in_speed, int32_t in_bits, int32_t in_mode, bool* _aidl_return);
    ndk::ScopedAStatus disconnect(bool* _aidl_return);
    ndk::ScopedAStatus sendByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
    ndk::ScopedAStatus readByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
    ndk::ScopedAStatus transferByte(const std::vector<uint8_t>& in_tx, std::vector<uint8_t>* out_rx, int32_t in_len, int8_t* _aidl_return);
};

}  // namespace spi
}  // namespace imx
}  // namespace hardware
}  // namespace android
}  // namespace aidl
