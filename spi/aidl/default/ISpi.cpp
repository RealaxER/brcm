// #define LOG_TAG "UART_DRIVER"

// #include <utils/Log.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <termios.h>
// #include <string.h>
// #include "IUart.h"

// namespace aidl {
// namespace android {
// namespace hardware {
// namespace rpi {
// namespace uart {

// struct termios options;
// int fd =  0;

// ndk::ScopedAStatus connect(const std::string& in_port, int32_t in_baud, bool* _aidl_return);
//     int fd = 0;
//     tcgetattr(fd, &options);
//     options.c_cflag = in_baud | CS8 | CLOCAL | CREAD;
//     options.c_iflag = IGNPAR;
//     options.c_oflag = 0;
//     options.c_lflag = 0;
//     tcflush(fd, TCIFLUSH);
//     tcsetattr(fd, TCSANOW, &options);

//     if(fd < 0){
//         *_aidl_return =  false;
//         return ndk::ScopedAStatus::fromServiceSpecificError(-1);
//     }
//     else {
//         *_aidl_return =  true;
//         return ndk::ScopedAStatus::ok();
//     }
// }

// //void putChars(in String msg);
// ndk::ScopedAStatus close(bool* _aidl_return);
//     close(fd);
//     return ndk::ScopedAStatus::ok();
// }


// ndk::ScopedAStatus sendByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return){
//     int8_t ret = write(fd, data, len);
//     *_aidl_return =  ret;
//     if(ret <  0){
//         return ndk::ScopedAStatus::fromServiceSpecificError(-1);
       
//     }else {
//         return ndk::ScopedAStatus::ok();
//     }
    
// }

// ndk::ScopedAStatus readByte(std::vector<uint8_t>* out_data, int32_t in_len, int8_t* _aidl_return){
//     int8_t ret = read(fd, data, len);
//     *_aidl_return =  ret;
//     if(ret <  0){
//         return ndk::ScopedAStatus::fromServiceSpecificError(-1);
//     }else {
//         return ndk::ScopedAStatus::ok();
//     }
// }

// }  // namespace uart
// }  // namespace rpi
// }  // namespace hardware
// }  // namespace android
// }  // namespace aidl
