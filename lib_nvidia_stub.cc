/**
 * @file lib_nvidia_stub.c
 * @author @2kai2kai2
 *
 * This is a stub for systems without any Nvidia GPUs (such as MacOS)
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

// initial
Napi::FunctionReference *NvidiaGPU::constructor = nullptr;

Napi::Value NvidiaGPU::allGPUs(const Napi::CallbackInfo &info) {
    return Napi::Array::New(info.Env());
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
    *constructor = Napi::Persistent(func);
    exports.Set("NvidiaGPU", func);
    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

NvidiaGPU::NvidiaGPU(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<NvidiaGPU>(info),
      lastSeenTimeStamp(0) {
    using namespace Napi;
    throw Error::New(
        info.Env(),
        "Nvidia GPUs are not supported on this device."
    );
}

NvidiaGPU::~NvidiaGPU() {}

Napi::Value NvidiaGPU::name(const Napi::CallbackInfo &info) {
    using namespace Napi;
    throw Error::New(
        info.Env(),
        "Nvidia GPUs are not supported on this device."
    );
}

Napi::Value NvidiaGPU::utilization(const Napi::CallbackInfo &info) {
    using namespace Napi;
    throw Error::New(
        info.Env(),
        "Nvidia GPUs are not supported on this device."
    );
}
