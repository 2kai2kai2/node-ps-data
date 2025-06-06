/**
 * @file lib_nvml.h
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

#pragma once
#include <napi.h>

struct nvmlDevice_st;
typedef nvmlDevice_st *nvmlDevice_t;

class NvidiaGPU : public Napi::ObjectWrap<NvidiaGPU> {
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    NvidiaGPU(const Napi::CallbackInfo &info);
    ~NvidiaGPU();
    static Napi::Value allGPUs(const Napi::CallbackInfo &info);

    /**
     * Gets the device's name as a `Napi::String`.
     *
     * No params.
     */
    Napi::Value name(const Napi::CallbackInfo &info);
    Napi::Value utilization(const Napi::CallbackInfo &info);

private:
    static Napi::FunctionReference *constructor;
    nvmlDevice_t device;
    unsigned long long lastSeenTimeStamp;
    uint32_t pid;
    // NvidiaGPU(const nvmlDevice_t device);
};
