#pragma once

#include <napi.h>

class Tesseract : public Napi::ObjectWrap<Tesseract>
{
  public:
    static Napi::Object Initialize(Napi::Env env, Napi::Object exports);
    Tesseract(const Napi::CallbackInfo &);
    void Init(const Napi::CallbackInfo &);
    Napi::Value GetUTF8Text(const Napi::CallbackInfo &);
    void SetImage(const Napi::CallbackInfo &);
    Napi::Value Greet(const Napi::CallbackInfo &);

    static Napi::Function GetClass(Napi::Env);

  private:
    static Napi::FunctionReference constructor;

    tesseract::TessBaseAPI *_api;
    std::string _greeterName;
};
