/**
 * @file lib_nvidia_nvml.cc
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
#include "lib_nvidia.h"
#include <nvml.h>

// initial
Napi::FunctionReference *NvidiaGPU::constructor = nullptr;

Napi::Value NvidiaGPU::allGPUs(const Napi::CallbackInfo &info) {
    using namespace Napi;
    nvmlReturn_t err = nvmlInit_v2();
    switch (err) {
    case NVML_SUCCESS:
        // Yay!
        break;
    case NVML_ERROR_DRIVER_NOT_LOADED:
        // If NVML doesn't exist, we have no compatible NVIDIA gpus.
        // If this is not the case, then something went wrong and the user
        // should submit an issue.
        return Array::New(info.Env());
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
        Object gpu = NvidiaGPU::constructor->New({Number::From(info.Env(), i)});
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
            InstanceMethod<&NvidiaGPU::name>(
                "name",
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
            InstanceMethod<&NvidiaGPU::memory>(
                "memory",
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
    if (info.Length() != 1) {
        throw Error::New(info.Env(), "Invalid number of arguments.");
    }
    this->deviceIdx = info[0].As<Number>().Uint32Value();

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

    err = nvmlDeviceGetHandleByIndex_v2(this->deviceIdx, &this->device);
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
    case NVML_SUCCESS: {
        std::string strName(name);
        strName += " (TOTAL)";
        return String::From(info.Env(), strName);
    }
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

    nvmlUtilization_t util = {};
    nvmlReturn_t err = nvmlDeviceGetUtilizationRates(this->device, &util);
    switch (err) {
    case NVML_SUCCESS: {
        Object obj = Object::New(info.Env());
        obj.Set("gpu", Number::From(info.Env(), ((double)util.gpu) / 100.0));
        obj.Set(
            "memoryRW",
            Number::From(info.Env(), ((double)util.memory) / 100.0)
        );
        return obj;
    }
    case NVML_ERROR_UNINITIALIZED:
        throw Error::New(
            info.Env(),
            "Found NVML uninitialized, this is likely an internal bug."
        );
    case NVML_ERROR_NO_PERMISSION:
        throw Error::New(
            info.Env(),
            "This program does not have permission to access this GPU."
        );
    case NVML_ERROR_INVALID_ARGUMENT:
        throw Error::New(info.Env(), "Unknown device.");
    case NVML_ERROR_GPU_IS_LOST:
        throw Error::New(
            info.Env(),
            "Due to a hardware issue, the GPU is inaccessible."
        );
    default:
        throw Error::New(info.Env(), "Failed to communicate with the device.");
    }
    // unreachable
}

Napi::Value NvidiaGPU::memory(const Napi::CallbackInfo &info) {
    using namespace Napi;

    nvmlMemory_t mem = {};
    nvmlReturn_t err = nvmlDeviceGetMemoryInfo(this->device, &mem);
    switch (err) {
    case NVML_SUCCESS: {
        Object obj = Object::New(info.Env());
        obj.Set("free", Number::From(info.Env(), mem.free));
        obj.Set("total", Number::From(info.Env(), mem.total));
        obj.Set("used", Number::From(info.Env(), mem.used));
        return obj;
    }
    case NVML_ERROR_UNINITIALIZED:
        throw Error::New(
            info.Env(),
            "Found NVML uninitialized, this is likely an internal bug."
        );
    case NVML_ERROR_NO_PERMISSION:
        throw Error::New(
            info.Env(),
            "This program does not have permission to access this GPU."
        );
    case NVML_ERROR_INVALID_ARGUMENT:
        throw Error::New(info.Env(), "Unknown device.");
    case NVML_ERROR_GPU_IS_LOST:
        throw Error::New(
            info.Env(),
            "Due to a hardware issue, the GPU is inaccessible."
        );
    default:
        throw Error::New(info.Env(), "Failed to communicate with the device.");
    }
}