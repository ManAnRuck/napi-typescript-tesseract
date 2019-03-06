const Tesseract = require("../dist/binding.js");
const assert = require("assert");

assert(Tesseract, "The expected module is undefined");

function testBasic()
{
    const instance = new Tesseract("mr-yeoman");
    assert(instance.greet, "The expected method is not defined");
    assert.strictEqual(instance.greet("kermit"), "mr-yeoman", "Unexpected value returned");
}

function testGetUTF8Text()
{
    const instance = new Tesseract("mr-yeoman");
    instance.Init();
    instance.SetImage();
    assert(instance.getUTF8Text, "The expected method is not defined");
    console.log(instance.getUTF8Text());
    delete instance;
}

function testInvalidParams()
{
    const instance = new Tesseract();
}

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
assert.doesNotThrow(testGetUTF8Text, undefined, "testGetUTF8Text threw an expection");
assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

console.log("Tests passed- everything looks OK!");