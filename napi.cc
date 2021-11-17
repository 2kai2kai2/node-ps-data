#include "lib.h"
#include <napi.h>

Napi::Number cpuUserTime(const Napi::CallbackInfo &info) {
    using namespace Napi;
    if (info.Length() != 1) {
        throw Error::New(info.Env(), "Invalid number of arguments.");
    }
    const size_t processid = info[0].ToNumber().Int64Value();
    size_t user;
    size_t kernel;
    if (!cpuTimeCpp(processid, user, kernel)) {
        return Number::New(info.Env(), 0);
    }
    Number num = Number::New(info.Env(), user);
    return Number::New(info.Env(), num);
}

Napi::Number cpuKernelTime(const Napi::CallbackInfo &info) {\
    using namespace Napi;
    if (info.Length() != 1) {
        throw Error::New(info.Env(), "Invalid number of arguments.");
    }
    const size_t processid = info[0].ToNumber().Int64Value();
    size_t user;
    size_t kernel;
    if (!cpuTimeCpp(processid, user, kernel)) {
        return Number::New(info.Env(), 0);
    }
    Number num = Number::New(info.Env(), kernel);
    return Number::New(info.Env(), num);
}

Napi::Number cpuTime(const Napi::CallbackInfo &info) {
    using namespace Napi;
    if (info.Length() != 1) {
        throw Error::New(info.Env(), "Invalid number of arguments.");
    }
    const size_t processid = info[0].ToNumber().Int64Value();
    size_t user;
    size_t kernel;
    if (!cpuTimeCpp(processid, user, kernel)) {
        return Number::New(info.Env(), 0);
    }
    Number num = Number::New(info.Env(), user + kernel);
    return Number::New(info.Env(), num);
}

Napi::Number memInfo(const Napi::CallbackInfo& info) {
    using namespace Napi;
    if (info.Length() != 1) {
        throw Error::New(info.Env(), "Invalid number of arguments.");
    }
    const size_t processid = info[0].ToNumber().Int64Value();
    Number num = Number::New(info.Env(), memInfoCpp(processid));
    return num;
}

Napi::Object Initialize(Napi::Env env, Napi::Object exports) {
    using namespace Napi;
    exports.Set(String::New(env, "cpuUserTime"), Function::New(env, cpuUserTime));
    exports.Set(String::New(env, "cpuKernelTime"), Function::New(env, cpuKernelTime));
    exports.Set(String::New(env, "cpuTime"), Function::New(env, cpuTime));
    exports.Set(String::New(env, "memInfo"), Function::New(env, memInfo));
    return exports;
}

NODE_API_MODULE(node_ps_data, Initialize)
