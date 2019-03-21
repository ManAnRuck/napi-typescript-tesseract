#pragma once
#include <tesseract/baseapi.h>
#include <napi.h>

class Tesseract : public Napi::ObjectWrap<Tesseract>
{
public:
  static Napi::Object Initialize(Napi::Env env, Napi::Object exports);
  Tesseract(const Napi::CallbackInfo &);
  ~Tesseract();
  void Init(const Napi::CallbackInfo &);
  Napi::Value GetUTF8Text(const Napi::CallbackInfo &);
  void SetImage(const Napi::CallbackInfo &);
  void ProcessPages(const Napi::CallbackInfo &);
  void End(const Napi::CallbackInfo &);

  static Napi::Function GetClass(Napi::Env);

private:
  static Napi::FunctionReference constructor;

  tesseract::TessBaseAPI *_api;
  std::string _greeterName;
  char *_getDatapath(const Napi::Value);
};
