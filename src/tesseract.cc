#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <string>

#include "tesseract.h"
#include "leptonica_pix.h"

using namespace Napi;

Napi::FunctionReference Tesseract::constructor;

Tesseract::Tesseract(const Napi::CallbackInfo &info) : ObjectWrap(info)
{
    Napi::Env env = info.Env();

    this->_api = new tesseract::TessBaseAPI();
}

Tesseract::~Tesseract()
{
    // this isn't called
    printf("destructor Tesseract::~Tesseract \n");
    this->_api->End();
}

void Tesseract::Init(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string language = "eng";
    const char *datapath;

    if (info[1].IsString())
    {
        language = info[1].As<Napi::String>().Utf8Value();
    }

    if (info[0].IsString())
    {
        // Utf8Value returns std::string
        datapath = info[0].As<Napi::String>().Utf8Value().c_str();
    }
    else
    {
        datapath = NULL;
    }
    // datapath should be NULL or the given path from info[0]
    // int tesseract::TessBaseAPI::Init(const char *datapath, const char *language)
    if (this->_api->Init(datapath, language.c_str()))
    {
        Napi::TypeError::New(env, "Could not initialize tesseract.")
            .ThrowAsJavaScriptException();
    }
}

void Tesseract::SetImage(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 1)
    {
        Napi::TypeError::New(env, "Wrong number of arguments")
            .ThrowAsJavaScriptException();
    }

    if (!info[0].IsObject() && !info[0].IsString())
    {
        Napi::TypeError::New(env, "Argument have to be an Image Path or Object")
            .ThrowAsJavaScriptException();
    }

    if (info[0].IsObject())
    {
        // LeptonicaPix *pixImage = LeptonicaPix::Unwrap(info[0].As<Napi::Object>());
        LeptonicaPix *pixImage = Napi::ObjectWrap<LeptonicaPix>::Unwrap(info[0].As<Napi::Object>());
        this->_api->SetImage(pixImage->Image());
    }

    if (info[0].IsString())
    {
        std::string file_path_input = info[0].As<Napi::String>().Utf8Value();

        // const char *file_path = file_path_input.c_str();
        std::vector<char> cstr(file_path_input.c_str(), file_path_input.c_str() + file_path_input.size() + 1);

        this->_api->SetImage(pixRead(&cstr[0]));
    }
}

Napi::Value Tesseract::GetUTF8Text(const Napi::CallbackInfo &info)
{
    char *outText;
    Napi::Env env = info.Env();
    // Get OCR result
    outText = this->_api->GetUTF8Text();
    // printf("OCR output:\n%s", outText);

    this->_api->End();

    return Napi::String::New(env, outText);
}

Napi::Object Tesseract::Initialize(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Tesseract",
                                      {
                                          Tesseract::InstanceMethod("Init", &Tesseract::Init),
                                          Tesseract::InstanceMethod("SetImage", &Tesseract::SetImage),
                                          Tesseract::InstanceMethod("getUTF8Text", &Tesseract::GetUTF8Text),
                                      });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Tesseract", func);
    return exports;
}

// Napi::Object Init(Napi::Env env, Napi::Object exports)
// {
//     Tesseract::Initialize(env, exports);
//     return exports;
// }

// NODE_API_MODULE(addon, Init)
