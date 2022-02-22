#include "lib.h"
#include <napi.h>

Napi::Number cpuUserTime(const Napi::CallbackInfo& info) {
    using namespace Napi;
    // Check that the correct number arguments were passed
    if (info.Length() != 1)
        throw Error::New(info.Env(), "Invalid number of arguments.");
    const size_t processid = info[0].ToNumber().Int64Value();
    // Run through platform-specific implementations; return 0 if not found.
    size_t user, kernel;
    if (!cpuTimeCpp(processid, user, kernel))
        return Number::New(info.Env(), 0);
    // Return if found
    return Number::New(info.Env(), user);
}

Napi::Number cpuKernelTime(const Napi::CallbackInfo& info) {
    using namespace Napi;
    // Check that the correct number arguments were passed
    if (info.Length() != 1)
        throw Error::New(info.Env(), "Invalid number of arguments.");
    const size_t processid = info[0].ToNumber().Int64Value();
    // Run through platform-specific implementations; return 0 if not found.
    size_t user, kernel;
    if (!cpuTimeCpp(processid, user, kernel))
        return Number::New(info.Env(), 0);
    // Return if found
    return Number::New(info.Env(), kernel);
}

Napi::Number cpuTime(const Napi::CallbackInfo& info) {
    using namespace Napi;
    // Check that the correct number arguments were passed
    if (info.Length() != 1)
        throw Error::New(info.Env(), "Invalid number of arguments.");
    const size_t processid = info[0].ToNumber().Int64Value();
    // Run through platform-specific implementations; return 0 if not found.
    size_t user, kernel;
    if (!cpuTimeCpp(processid, user, kernel))
        return Number::New(info.Env(), 0);
    // Return if found
    return Number::New(info.Env(), user + kernel);
}

Napi::Number memInfo(const Napi::CallbackInfo& info) {
    using namespace Napi;
    // Check that the correct number arguments were passed
    if (info.Length() != 1)
        throw Error::New(info.Env(), "Invalid number of arguments.");
    const size_t processid = info[0].ToNumber().Int64Value();
    // Run through platform-specific implementations; return 0 if not found.
    size_t total, rss;
    if (!memInfoCpp(processid, total, rss))
        return Number::New(info.Env(), 0);
    // Return if found
    return Number::New(info.Env(), total);
}

Napi::Number fileReadBytes(const Napi::CallbackInfo& info) {
    using namespace Napi;
    // Check that the correct number arguments were passed
    if (info.Length() != 1)
        throw Error::New(info.Env(), "Invalid number of arguments.");
    const size_t processid = info[0].ToNumber().Int64Value();
    // Run platform-specific implementations; return 0 if not found.
    size_t readSize, readCount, writeSize, writeCount;
    if (!fileInfoCpp(processid, readSize, readCount, writeSize, writeCount))
        return Number::New(info.Env(), 0);
    // Return if found
    return Number::New(info.Env(), readSize);
}

Napi::Number fileWriteBytes(const Napi::CallbackInfo& info) {
    using namespace Napi;
    // Check that the correct number arguments were passed
    if (info.Length() != 1)
        throw Error::New(info.Env(), "Invalid number of arguments.");
    const size_t processid = info[0].ToNumber().Int64Value();
    // Run platform-specific implementations; return 0 if not found.
    size_t readSize, readCount, writeSize, writeCount;
    if (!fileInfoCpp(processid, readSize, readCount, writeSize, writeCount))
        return Number::New(info.Env(), 0);
    // Return if found
    return Number::New(info.Env(), writeSize);
}

Napi::Object Initialize(Napi::Env env, Napi::Object exports) {
    using namespace Napi;
    exports.Set(String::New(env, "cpuUserTime"), Function::New(env, cpuUserTime));
    exports.Set(String::New(env, "cpuKernelTime"), Function::New(env, cpuKernelTime));
    exports.Set(String::New(env, "cpuTime"), Function::New(env, cpuTime));
    exports.Set(String::New(env, "memInfo"), Function::New(env, memInfo));
    exports.Set(String::New(env, "fileRead"), Function::New(env, fileReadBytes));
    exports.Set(String::New(env, "fileWrite"), Function::New(env, fileWriteBytes));
    return exports;
}

NODE_API_MODULE(node_ps_data, Initialize)
