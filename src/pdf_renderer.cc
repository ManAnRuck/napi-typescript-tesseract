
#include <tesseract/baseapi.h>
#include <tesseract/renderer.h>

#include "pdf_renderer.h"

using namespace Napi;

Napi::FunctionReference PdfRenderer::constructor;

PdfRenderer::PdfRenderer(const Napi::CallbackInfo &info) : Napi::ObjectWrap<PdfRenderer>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    std::string outputPath = "";
    std::string datapath = "./";

    if (info[0].IsString())
    {
        outputPath = info[0].As<Napi::String>().Utf8Value();
    }

    if (info[1].IsString())
    {
        datapath = info[1].As<Napi::String>().Utf8Value();
    }

    bool textonly = false;
    if (info[2].IsBoolean())
    {
        textonly = info[2].As<Napi::Boolean>().ToBoolean();
    }

    // std::string file_path_input = info[0].As<Napi::String>().Utf8Value();

    // const char *file_path = file_path_input.c_str();
    this->_renderer = new tesseract::TessPDFRenderer(outputPath.c_str(), datapath.c_str(), textonly);
}

Napi::Object PdfRenderer::Initialize(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "PdfRenderer", {});

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("PdfRenderer", func);
    return exports;
}
