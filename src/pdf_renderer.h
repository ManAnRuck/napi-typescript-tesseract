#pragma once
#include <tesseract/renderer.h>
#include <napi.h>

class PdfRenderer : public Napi::ObjectWrap<PdfRenderer>
{
public:
  static Napi::Object Initialize(Napi::Env env, Napi::Object exports);
  PdfRenderer(const Napi::CallbackInfo &info);

  tesseract::TessPDFRenderer *_renderer;

private:
  static Napi::FunctionReference constructor;
};
