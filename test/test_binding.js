const { Tesseract, Image } = require("../dist/binding.js");
const assert = require("assert");

console.log({Tesseract, Image})

assert(Tesseract, "The expected module is undefined");

function createImage()
{
    const image = new Image("/Users/manuelruck/Desktop/image.png");
    console.log("Image:", image);
}

function testGetUTF8TextFromFilePath()
{
    const tesseract = new Tesseract();
    tesseract.Init();
    tesseract.SetImage(`${__dirname}/image.png`);
    console.log(tesseract.getUTF8Text());
}

function testGetUTF8TextFromImageObject()
{
    const tesseract = new Tesseract();
    tesseract.Init(null, "eng");

    const image = new Image(`${__dirname}/image.png`)

    tesseract.SetImage(image);
    console.log(tesseract.getUTF8Text());
}


assert.doesNotThrow(createImage, undefined, "createImage threw an expection");
assert.doesNotThrow(testGetUTF8TextFromFilePath, undefined, "testGetUTF8TextFromFilePath threw an expection");
assert.doesNotThrow(testGetUTF8TextFromImageObject, undefined, "testGetUTF8TextFromImageObject threw an expection");

console.log("Tests passed- everything looks OK!");