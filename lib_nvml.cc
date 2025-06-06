/**
 * @file lib_nvml.cc
 * @author @2kai2kai2
 *
 * @copyright Copyright (c) 2025 2kai2kai2
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "lib_nvml.h"

// initial
Napi::FunctionReference *NvidiaGPU::constructor = nullptr;

Napi::Value NvidiaGPU::allGPUs(const Napi::CallbackInfo &info) {
    using namespace Napi;
    // Check that the correct number arguments were passed
    if (info.Length() != 1) {
        throw Error::New(info.Env(), "Invalid number of arguments.");
    }

    uint32_t pid = info[0].As<Number>().Uint32Value();

    nvmlReturn_t err = nvmlInit_v2();
    switch (err) {
    case NVML_SUCCESS:
        // Yay!
        break;
    case NVML_ERROR_DRIVER_NOT_LOADED:
        // If NVML doesn't exist, we have no compatible NVIDIA gpus.
        // If this is not the case, then something went wrong and the user
        // should submit an issue.
        return Napi::Array::New(info.Env());
    case NVML_ERROR_NO_PERMISSION:
        throw Error::New(
            info.Env(),
            "The program does not have permission to talk to the Nvidia NVML "
            "drivers."
        );
    default:
        throw Error::New(info.Env(), "An unknown NVML error has occurred.");
    }

    unsigned int device_count;
    err = nvmlDeviceGetCount_v2(&device_count);
    switch (err) {
    case NVML_SUCCESS: break;
    case NVML_ERROR_UNINITIALIZED:
        throw Error::New(
            info.Env(),
            "Found NVML uninitialized, this is likely an internal bug."
        );
    case NVML_ERROR_INVALID_ARGUMENT:
        nvmlShutdown();
        throw Error::New(
            info.Env(),
            "Found device count nullptr, this shouldn't be able to happen."
        );
    default:
        nvmlShutdown();
        throw Error::New(info.Env(), "An unknown NVML error has occurred.");
    }

    Array array = Array::New(info.Env());
    for (uint32_t i = 0; i < device_count; ++i) {
        Object gpu = NvidiaGPU::constructor->New({
            Number::From(info.Env(), i),
            Number::From(info.Env(), pid),
        });
        array.Set(i, gpu);
    }

    // each GPU handle has its own reference counted,
    // we can clear the allGPUs one
    nvmlShutdown();

    return array;
}

Napi::Object NvidiaGPU::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(
        env,
        "NvidiaGPU",
        {
            StaticMethod<&NvidiaGPU::allGPUs>(
                "allGPUs",
                static_cast<napi_property_attributes>(
                    napi_writable | napi_configurable
                )
            ),
            InstanceMethod<&NvidiaGPU::utilization>(
                "utilization",
                static_cast<napi_property_attributes>(
                    napi_writable | napi_configurable
                )
            ),
            InstanceMethod<&NvidiaGPU::name>(
                "name",
                static_cast<napi_property_attributes>(
                    napi_writable | napi_configurable
                )
            ),
        }
    );

    NvidiaGPU::constructor = new Napi::FunctionReference();
    *NvidiaGPU::constructor = Napi::Persistent(func);
    exports.Set("NvidiaGPU", func);
    env.SetInstanceData<Napi::FunctionReference>(NvidiaGPU::constructor);

    return exports;
}

NvidiaGPU::NvidiaGPU(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<NvidiaGPU>(info),
      lastSeenTimeStamp(0) {
    using namespace Napi;
    // Check that the correct number arguments were passed
    if (info.Length() != 2) {
        throw Error::New(info.Env(), "Invalid number of arguments.");
    }
    uint32_t device_idx = info[0].As<Number>().Uint32Value();
    this->pid = info[1].As<Number>().Uint32Value();

    nvmlReturn_t err = nvmlInit_v2();
    switch (err) {
    case NVML_SUCCESS: break;
    case NVML_ERROR_DRIVER_NOT_LOADED:
        throw Error::New(
            info.Env(),
            "This system does not seem have NVML drivers."
        );
    case NVML_ERROR_NO_PERMISSION:
        throw Error::New(
            info.Env(),
            "The program does not have permission to talk to the Nvidia NVML "
            "drivers."
        );
    default:
        throw Error::New(info.Env(), "An unknown NVML error has occurred.");
    }

    err = nvmlDeviceGetHandleByIndex_v2(device_idx, &this->device);
    switch (err) {
    case NVML_SUCCESS: break;
    case NVML_ERROR_UNINITIALIZED:
        throw Error::New(
            info.Env(),
            "Found NVML uninitialized, this is likely an internal bug."
        );
    case NVML_ERROR_INVALID_ARGUMENT:
        throw Error::New(info.Env(), "Invalid GPU device index.");
    case NVML_ERROR_NO_PERMISSION:
        throw Error::New(
            info.Env(),
            "The program does not have permission to talk to this GPU."
        );
    default:
        throw Error::New(info.Env(), "Failed to communicate with the device.");
    }
}

NvidiaGPU::~NvidiaGPU() { nvmlShutdown(); }

Napi::Value NvidiaGPU::name(const Napi::CallbackInfo &info) {
    using namespace Napi;
    char name[NVML_DEVICE_NAME_V2_BUFFER_SIZE] = {0};
    nvmlReturn_t err =
        nvmlDeviceGetName(this->device, name, NVML_DEVICE_NAME_V2_BUFFER_SIZE);
    switch (err) {
    case NVML_SUCCESS: return String::From(info.Env(), name);
    case NVML_ERROR_UNINITIALIZED:
        throw Error::New(
            info.Env(),
            "Found NVML uninitialized, this is likely an internal bug."
        );
    case NVML_ERROR_INVALID_ARGUMENT:
        throw Error::New(info.Env(), "Unknown device.");
    case NVML_ERROR_INSUFFICIENT_SIZE:
        throw Error::New(
            info.Env(),
            "Failed to get name due to insufficient buffer size. Try updating "
            "`node-ps-data` or open an issue."
        );
    case NVML_ERROR_GPU_IS_LOST:
        throw Error::New(
            info.Env(),
            "Due to a hardware issue, the GPU is inaccessible."
        );
    default:
        throw Error::New(info.Env(), "Failed to communicate with the device.");
    }
}

Napi::Value NvidiaGPU::utilization(const Napi::CallbackInfo &info) {
    using namespace Napi;

    unsigned int processSamplesCount = 0;

    nvmlReturn_t err = nvmlDeviceGetProcessUtilization(
        this->device,
        NULL,
        &processSamplesCount,
        this->lastSeenTimeStamp
    );
    switch (err) {
    case NVML_SUCCESS: break;
    case NVML_ERROR_UNINITIALIZED:
        throw Error::New(
            info.Env(),
            "Found NVML uninitialized, this is likely an internal bug."
        );
    case NVML_ERROR_INVALID_ARGUMENT:
        throw Error::New(info.Env(), "Unknown device.");
    case NVML_ERROR_NOT_SUPPORTED:
        throw Error::New(
            info.Env(),
            "This device does not support this operation."
        );
    case NVML_ERROR_NOT_FOUND: {
        printf("not_found_initial");
        Object ret = Object::New(info.Env());
        ret.Set("smUtilization", Number::From(info.Env(), 0));
        return ret;
    }
    case NVML_ERROR_GPU_IS_LOST:
        throw Error::New(
            info.Env(),
            "Due to a hardware issue, the GPU is inaccessible."
        );
    case NVML_ERROR_INSUFFICIENT_SIZE:
        // it is not documented for this function, but like
        // `nvmlDeviceGetProcessesUtilizationInfo`, it should usually return
        // this error with the `NULL, 0` arguments
        break;
    default:
        throw Error::New(info.Env(), "Failed to communicate with the device.");
    }

    // retry because I imagine race conditions might cause process_count to
    // become invalid
    for (uint32_t i = 0; i < 5; i++) {
        // allocate a bit extra space to hopefully avoid the retry
        processSamplesCount += 4;
        nvmlProcessUtilizationSample_t *array =
            new nvmlProcessUtilizationSample_t[processSamplesCount];

        err = nvmlDeviceGetProcessUtilization(
            this->device,
            array,
            &processSamplesCount,
            this->lastSeenTimeStamp
        );
        switch (err) {
        case NVML_SUCCESS: {
            // success!
            for (unsigned int process_idx = 0;
                 process_idx < processSamplesCount;
                 process_idx++) {
                if (array[process_idx].pid != this->pid) {
                    continue;
                }
                this->lastSeenTimeStamp = array[process_idx].timeStamp;
                unsigned int smUtil = array[process_idx].smUtil;
                delete[] array;

                printf("success");
                Object ret = Object::New(info.Env());
                ret.Set("smUtilization", Number::From(info.Env(), smUtil));
                return ret;
            }
            // if not in array, there has been no utilization
            delete[] array;
            printf("not in array (len %d)", processSamplesCount - 4);
            Object ret = Object::New(info.Env());
            ret.Set("smUtilization", Number::From(info.Env(), 0));
            return ret;
        }
        case NVML_ERROR_UNINITIALIZED:
            delete[] array;
            throw Error::New(
                info.Env(),
                "Found NVML uninitialized, this is likely an internal bug."
            );
        case NVML_ERROR_INVALID_ARGUMENT:
            delete[] array;
            throw Error::New(info.Env(), "Unknown device.");
        case NVML_ERROR_NOT_SUPPORTED:
            delete[] array;
            throw Error::New(
                info.Env(),
                "This device does not support this operation."
            );
        case NVML_ERROR_NOT_FOUND: {
            delete[] array;
            printf("not_found_later");
            Object ret = Object::New(info.Env());
            ret.Set("smUtilization", Number::From(info.Env(), 0));
            return ret;
        }
        case NVML_ERROR_GPU_IS_LOST:
            delete[] array;
            throw Error::New(
                info.Env(),
                "Due to a hardware issue, the GPU is inaccessible."
            );
        case NVML_ERROR_ARGUMENT_VERSION_MISMATCH:
            delete[] array;
            throw Error::New(
                info.Env(),
                "Likely Internal issue: argument version mismatch."
            );
        case NVML_ERROR_INSUFFICIENT_SIZE: delete[] array; continue; // retry
        default:
            delete[] array;
            throw Error::New(
                info.Env(),
                "Failed to communicate with the device."
            );
        }
    }

    // retries failed
    throw Error::New(
        info.Env(),
        "Too many retries. This is very unlikely and probably means there is "
        "an internal issue."
    );
}
