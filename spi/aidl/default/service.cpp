#define LOG_TAG "SPI_SERVICE"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "Spi.h"

using aidl::android::hardware::imx::spi::Spi;
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

    std::shared_ptr<Spi> spi = ndk::SharedRefBase::make<Spi>();
    const std::string name = Spi::descriptor + "/default"s;

    if (spi != nullptr) {
        if(AServiceManager_addService(spi->asBinder().get(), name.c_str()) != STATUS_OK) {
            loge("Failed to register ISpi service");
            return -1;
        }
    } else {
        loge("Failed to get ISpi instance");
        return -1;
    }

    logd("ISpi service starts to join service pool");
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE;  // should not reached
}
