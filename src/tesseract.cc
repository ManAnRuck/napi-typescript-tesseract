#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <string>
#include <iostream>

#include "tesseract.h"
#include "leptonica_pix.h"
#include "pdf_renderer.h"

using namespace Napi;

Napi::FunctionReference Tesseract::constructor;

Tesseract::Tesseract(const Napi::CallbackInfo &info) : ObjectWrap(info)
{
    this->_api = new tesseract::TessBaseAPI();
}

Tesseract::~Tesseract()
{
    // this isn't called
    this->_api->End();
}

const char *cStringOrNull(const std::string &s)
{
    return s == "" ? nullptr : s.c_str();
}

void Tesseract::Init(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string language = "eng";
    std::string datapath = "";

    if (info[1].IsString())
    {
        language = info[1].As<Napi::String>().Utf8Value();
    }

    if (info[0].IsString())
    {
        datapath = info[0].As<Napi::String>().Utf8Value();
    }

    if (this->_api->Init(cStringOrNull(datapath), language.c_str()))
    {
        Napi::TypeError::New(env, "Could not initialize tesseract.")
            .ThrowAsJavaScriptException();
    }
}

void Tesseract::ProcessPages(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    PdfRenderer *renderer;
    std::string input_image = "";
    int timeout_ms;

    if (info[0].IsString())
    {
        input_image = info[0].As<Napi::String>().Utf8Value();
    }

    if (info[2].IsNumber())
    {
        timeout_ms = info[2].As<Napi::Number>().Int32Value();
    }

    if (info[3].IsObject())
    {
        // LeptonicaPix *pixImage = LeptonicaPix::Unwrap(info[0].As<Napi::Object>());
        renderer = Napi::ObjectWrap<PdfRenderer>::Unwrap(info[3].As<Napi::Object>());
    }
    else
    {
        Napi::TypeError::New(env, "No PDF Renderer found.")
            .ThrowAsJavaScriptException();
        return;
    }
    // const char *input_image = "/Users/manuelruck/Desktop/image.png";
    const char *retry_config = nullptr;
    bool succeed = this->_api->ProcessPages(input_image.c_str(), retry_config, timeout_ms, renderer->_renderer);
    if (!succeed)
    {
        Napi::TypeError::New(env, "Error during processing.")
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

    return Napi::String::New(env, outText);
}

Napi::Object Tesseract::Initialize(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Tesseract",
                                      {
                                          Tesseract::InstanceMethod("Init", &Tesseract::Init),
                                          Tesseract::InstanceMethod("SetImage", &Tesseract::SetImage),
                                          Tesseract::InstanceMethod("ProcessPages", &Tesseract::ProcessPages),
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
