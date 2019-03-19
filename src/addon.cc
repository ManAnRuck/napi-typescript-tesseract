#include <napi.h>
#include "tesseract.h"
#include "leptonica_pix.h"
#include "pdf_renderer.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports)
{
    Tesseract::Initialize(env, exports);
    LeptonicaPix::Initialize(env, exports);
    PdfRenderer::Initialize(env, exports);
    return exports;
}

NODE_API_MODULE(addon, InitAll)