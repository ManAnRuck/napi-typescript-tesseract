let addon: any;
var fs = require("fs");
if (fs.existsSync("../build/Release")) {
  addon = require("../build/Release/tesseract-native");
} else {
  addon = require("../build/Debug/tesseract-native");
}

interface ITesseractNative {
  Init(dataPath?: string, language?: string): void;
  SetImage(image: any): void;
  getUTF8Text(): string;
}

class Tesseract {
  constructor() {
    this._addonInstance = new addon.Tesseract();
  }

  Init(dataPath?: string, language: string = "eng") {
    return this._addonInstance.Init();
  }

  SetImage(image: any) {
    return this._addonInstance.SetImage(image);
  }

  getUTF8Text() {
    return this._addonInstance.getUTF8Text();
  }

  // private members
  private _addonInstance: ITesseractNative;
}

export = Tesseract;
