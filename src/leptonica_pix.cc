#include <leptonica/allheaders.h>

#include "leptonica_pix.h"

using namespace Napi;

Napi::FunctionReference LeptonicaPix::constructor;

LeptonicaPix::LeptonicaPix(const Napi::CallbackInfo &info) : Napi::ObjectWrap<LeptonicaPix>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments")
            .ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "You need to name yourself")
            .ThrowAsJavaScriptException();
        return;
    }

    std::string file_path_input = info[0].As<Napi::String>().Utf8Value();

    // const char *file_path = file_path_input.c_str();
    std::vector<char> cstr(file_path_input.c_str(), file_path_input.c_str() + file_path_input.size() + 1);

    this->_image = pixRead(&cstr[0]);
}

Napi::Object LeptonicaPix::Initialize(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Image", {});

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Image", func);
    return exports;
}
