#define LOG_TAG "UART_SERVICE"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "I2c.h"

using aidl::android::hardware::imx::i2c::I2c;
using std::string_literals::operator""s;

void logd(std::string msg) {
    std::cout << msg << std::endl;
    ALOGD("%s", msg.c_str());
}

void loge(std::string msg) {
    std::cout << msg << std::endl;
    ALOGE("%s", msg.c_str());
}

int main() {
    // Enable vndbinder to allow vendor-to-venfor binder call
    android::ProcessState::initWithDriver("/dev/vndbinder");

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    ABinderProcess_startThreadPool();

    std::shared_ptr<I2c> i2c = ndk::SharedRefBase::make<I2c>();
    const std::string name = I2c::descriptor + "/default"s;

    if (i2c != nullptr) {
        if(AServiceManager_addService(i2c->asBinder().get(), name.c_str()) != STATUS_OK) {
            loge("Failed to register IUart service");
            return -1;
        }
    } else {
        loge("Failed to get IUart instance");
        return -1;
    }

    logd("IUart service starts to join service pool");
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE;  // should not reached
}
