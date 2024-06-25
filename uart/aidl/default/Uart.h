#pragma once

#include <aidl/android/hardware/imx/uart/BnUart.h>

namespace aidl {
namespace android {
namespace hardware {
namespace imx {
namespace uart {

class Uart : public BnUart {
    public:
    virtual ~Uart(); // Virtual destructor
    ndk::ScopedAStatus connect(const std::string& in_port, int32_t in_baud, bool* _aidl_return);
    ndk::ScopedAStatus disconnect(bool* _aidl_return);
    ndk::ScopedAStatus sendByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
    ndk::ScopedAStatus readByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
};

}  // namespace uart
}  // namespace imx
}  // namespace hardware
}  // namespace android
}  // namespace aidl
