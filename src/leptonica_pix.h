#pragma once
#include <leptonica/allheaders.h>
#include <napi.h>

class LeptonicaPix : public Napi::ObjectWrap<LeptonicaPix>
{
public:
  static Napi::Object Initialize(Napi::Env env, Napi::Object exports);
  LeptonicaPix(const Napi::CallbackInfo &info);
  Pix *Image() const { return _image; }

  Pix *_image;

private:
  static Napi::FunctionReference constructor;
  Napi::Value GetImage(const Napi::CallbackInfo &info);
};
