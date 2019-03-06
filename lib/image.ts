let addon: any;
var fs = require("fs");
if (fs.existsSync("../build/Release")) {
  addon = require("../build/Release/tesseract-native");
} else {
  addon = require("../build/Debug/tesseract-native");
}

interface IImage {
  _image: any;
}

class Image {
  constructor(filePath: string) {
    this._addonInstance = new addon.Image(filePath);
  }

  // private members
  private _addonInstance: IImage;
}

export = Image;
