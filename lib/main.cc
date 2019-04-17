#include <napi.h>
#include "core/connection.hh"

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    return Connection::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)