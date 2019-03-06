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

function testGetUTF8Text()
{
    const instance = new Tesseract("mr-yeoman");
    instance.Init();

    const image = new Image("/Users/manuelruck/Desktop/image.png")

    instance.SetImage(image);
    // assert(instance.getUTF8Text, "The expected method is not defined");
    // console.log(instance.getUTF8Text());
}

function testInvalidParams()
{
    const instance = new Tesseract();
}

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
assert.doesNotThrow(createImage, undefined, "createImage threw an expection");
assert.doesNotThrow(testGetUTF8Text, undefined, "testGetUTF8Text threw an expection");
assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

console.log("Tests passed- everything looks OK!");