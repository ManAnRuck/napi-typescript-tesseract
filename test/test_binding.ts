const { Tesseract, Image, PdfRenderer } = require("../lib/binding");
const assert = require("assert");
// const { langPath } = require("@tessdata/deu");
const langPath = `${__dirname}/../../tessdata`;

console.log({ Tesseract, Image });

assert(Tesseract, "The expected module is undefined");

function createImage() {
  const image = new Image(`${__dirname}/image.png`);
  console.log("Image:", image);
}

function testGetUTF8TextFromFilePath() {
  const tesseract = new Tesseract();
  tesseract.Init();
  tesseract.SetImage(`${__dirname}/image.png`);
  console.log(tesseract.getUTF8Text());
  tesseract.End();
}

function testGetUTF8TextFromImageObject() {
  const tesseract = new Tesseract();
  tesseract.Init(langPath, "deu");

  const image = new Image(`${__dirname}/image.png`);

  tesseract.SetImage(image);
  console.log(tesseract.getUTF8Text());
  tesseract.End();
}

function testSearchablePdf() {
  const tesseract = new Tesseract();
  tesseract.Init(langPath, "deu");
  const pdfRenderer = new PdfRenderer({
    outputBase: "test_pdf"
  });
  tesseract.ProcessPages({
    imagePath: `${__dirname}/image.png`,
    renderer: pdfRenderer
  });
  pdfRenderer.EndDocument();
  tesseract.End();
}

assert.doesNotThrow(createImage, undefined, "createImage threw an expection");
assert.doesNotThrow(
  testGetUTF8TextFromFilePath,
  undefined,
  "testGetUTF8TextFromFilePath threw an expection"
);
assert.doesNotThrow(
  testGetUTF8TextFromImageObject,
  undefined,
  "testGetUTF8TextFromImageObject threw an expection"
);
assert.doesNotThrow(
  testSearchablePdf,
  undefined,
  "testSearchablePdf threw an expection"
);

console.log("Tests passed- everything looks OK!");
