//
// Created by Twometer on 26/10/2022.
//

#include "ps3eye.hpp"

#define DRIVERLIB_API extern "C" [[maybe_unused]] __declspec(dllexport)
#define CAM(handle) (((CameraHandle*) handle)->camera)

struct CameraHandle {
    std::shared_ptr<ps3eye::camera> camera;
};

DRIVERLIB_API void *open_camera(int idx, int resolution, int fps, int format) {
    auto cams = ps3eye::list_devices();
    auto cam = cams[idx];
    if (!cam->init(static_cast<ps3eye::resolution>(resolution), fps, static_cast<ps3eye::format>(ps3eye::fmt_BGR))) {
        return nullptr;
    }

    if (!cam->start()) {
        return nullptr;
    }

    return (void *) (new CameraHandle{cam});
}

DRIVERLIB_API void set_auto_gain(void *handle, bool auto_gain) {
    CAM(handle)->set_auto_gain(auto_gain);
}

DRIVERLIB_API void set_awb(void *handle, bool awb) {
    CAM(handle)->set_awb(awb);
}

DRIVERLIB_API void set_exposure(void *handle, int exposure) {
    CAM(handle)->set_exposure(exposure);
}

DRIVERLIB_API void set_gain(void *handle, int gain) {
    CAM(handle)->set_gain(gain);
}

DRIVERLIB_API void set_framerate(void *handle, int fps) {
    CAM(handle)->set_framerate(fps);
}

DRIVERLIB_API void set_flip_status(void *handle, bool horizontal, bool vertical) {
    CAM(handle)->set_flip_status(horizontal, vertical);
}

DRIVERLIB_API void error_code(void *handle) {
    CAM(handle)->error_code();
}

DRIVERLIB_API const char *error_string(void *handle) {
    return CAM(handle)->error_string();
}

// TODO more wrapper functions

DRIVERLIB_API bool get_frame(void *handle, uint8_t *dst) {
    return CAM(handle)->get_frame(dst);
}

DRIVERLIB_API void close_camera(void *handle) {
    auto cam = (CameraHandle *) handle;
    cam->camera->stop();
    delete cam;
}