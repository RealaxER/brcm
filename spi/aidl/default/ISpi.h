// #pragma once

// #include <aidl/android/hardware/rpi/uart/BnUart.h>

// namespace aidl {
// namespace android {
// namespace hardware {
// namespace rpi {
// namespace uart {

// class Uart : public BnUart {
//     public:
//     ndk::ScopedAStatus connect(const std::string& in_port, int32_t in_baud, bool* _aidl_return);
//     ndk::ScopedAStatus close(bool* _aidl_return);
//     ndk::ScopedAStatus sendByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
//     ndk::ScopedAStatus readByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return);
//     ndk::ScopedAStatus transferByte(const std::vector<uint8_t>& in_tx, std::vector<uint8_t>* out_rx, int32_t in_len, int8_t* _aidl_return);
// };

// }  // namespace uart
// }  // namespace rpi
// }  // namespace hardware
// }  // namespace android
// }  // namespace aidl
