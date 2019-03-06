let addon: any;
var fs = require("fs");
if (fs.existsSync("../build/Release")) {
  addon = require("../build/Release/tesseract-native");
} else {
  addon = require("../build/Debug/tesseract-native");
}

class Image {
  constructor(filePath: string) {
    return new addon.Image(filePath);
  }
}

export = Image;
