#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "tesseract.h"

using namespace Napi;

Napi::FunctionReference Tesseract::constructor;

Tesseract::Tesseract(const Napi::CallbackInfo &info) : ObjectWrap(info)
{
    Napi::Env env = info.Env();

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

    this->_api = new tesseract::TessBaseAPI();

    this->_greeterName = info[0].As<Napi::String>().Utf8Value();
}

Napi::Value Tesseract::Greet(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "You need to introduce yourself to greet")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    // Napi::String name = info[0].As<Napi::String>();

    // printf("Hello %s\n", name.Utf8Value().c_str());
    // printf("I'm %s\n", this->_greeterName.c_str());

    return Napi::String::New(env, this->_greeterName);
}

void Tesseract::Init(const Napi::CallbackInfo &info)
{
    char *outText;
    Napi::Env env = info.Env();

    if (this->_api->Init(NULL, "eng"))
    {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
}

void Tesseract::SetImage(const Napi::CallbackInfo &info)
{
    char *outText;
    Napi::Env env = info.Env();

    // Open input image with leptonica library
    Pix *image = pixRead("/Users/manuelruck/Desktop/image.png");
    this->_api->SetImage(image);
}

Napi::Value Tesseract::GetUTF8Text(const Napi::CallbackInfo &info)
{
    char *outText;
    Napi::Env env = info.Env();
    // Get OCR result
    outText = this->_api->GetUTF8Text();
    // printf("OCR output:\n%s", outText);

    return Napi::String::New(env, outText);
}

Napi::Function Tesseract::GetClass(Napi::Env env)
{
    return DefineClass(env, "Tesseract",
                       {
                           Tesseract::InstanceMethod("Init", &Tesseract::Init),
                           Tesseract::InstanceMethod("SetImage", &Tesseract::SetImage),
                           Tesseract::InstanceMethod("greet", &Tesseract::Greet),
                           Tesseract::InstanceMethod("getUTF8Text", &Tesseract::GetUTF8Text),
                       });
}

Napi::Object Tesseract::Initialize(Napi::Env env, Napi::Object exports)
{
    Napi::Function func = Tesseract::GetClass(env);

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    Napi::String name = Napi::String::New(env, "Tesseract");
    exports.Set(name, func);
    return exports;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    Tesseract::Initialize(env, exports);
    return exports;
}

NODE_API_MODULE(addon, Init)
