let addon: any;
var fs = require("fs");
if (fs.existsSync("../build/Release")) {
  addon = require("../build/Release/tesseract-native");
} else {
  addon = require("../build/Debug/tesseract-native");
}
// const Tesseract = require("./tesseract");
import Tesseract = require("./tesseract");
import Image = require("./image");

export = { Tesseract, Image };
