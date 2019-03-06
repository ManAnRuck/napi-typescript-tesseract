const { Tesseract, Image } = require("../dist/binding.js");
const assert = require("assert");

console.log({Tesseract, Image})

assert(Tesseract, "The expected module is undefined");

function testBasic()
{
    const instance = new Tesseract("mr-yeoman");
    assert(instance.greet, "The expected method is not defined");
    assert.strictEqual(instance.greet("kermit"), "mr-yeoman", "Unexpected value returned");
}

function createImage()
{
    const image = new Image("/Users/manuelruck/Desktop/image.png");
    console.log("Image:", image);
}

function testGetUTF8TextFromFilePath()
{
    const tesseract = new Tesseract("mr-yeoman");
    tesseract.Init();
    tesseract.SetImage(`${__dirname}/image.png`);
    console.log(tesseract.getUTF8Text());
}

function testGetUTF8TextFromImageObject()
{
    const tesseract = new Tesseract("mr-yeoman");
    tesseract.Init();

    const image = new Image("/Users/manuelruck/Desktop/image.png")
    console.log(image)

    tesseract.SetImage(image);
    // console.log(tesseract.getUTF8Text());
}

function testInvalidParams()
{
    const instance = new Tesseract();
}

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
assert.doesNotThrow(createImage, undefined, "createImage threw an expection");
assert.doesNotThrow(testGetUTF8TextFromFilePath, undefined, "testGetUTF8TextFromFilePath threw an expection");
assert.doesNotThrow(testGetUTF8TextFromImageObject, undefined, "testGetUTF8TextFromImageObject threw an expection");
assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

console.log("Tests passed- everything looks OK!");