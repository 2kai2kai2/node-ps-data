#include "lib.h"
#include <napi.h>

Napi::Number cpuTime(const Napi::CallbackInfo &info) {
    if (info.Length() != 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments.");
    }
    const size_t processid = info[0].ToNumber().Int64Value();
    auto num = Napi::Number::New(info.Env(), cpuTimeCpp(processid));
    return Napi::Number::New(info.Env(), num);
}

Napi::Number memInfo(const Napi::CallbackInfo& info) {
    if (info.Length() != 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments.");
    }
    const size_t processid = info[0].ToNumber().Int64Value();
    auto num = Napi::Number::New(info.Env(), memInfoCpp(processid));
    return num;
}

Napi::Object Initialize(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "cpuTime"), Napi::Function::New(env, cpuTime));
    exports.Set(Napi::String::New(env, "memInfo"), Napi::Function::New(env, memInfo));
    return exports;
}

NODE_API_MODULE(node_ps_data, Initialize)
