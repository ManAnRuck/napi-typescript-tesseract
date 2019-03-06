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
  greet(strName: string): string;
  getUTF8Text(): string;
}

class Tesseract {
  constructor(name: string) {
    this._addonInstance = new addon.Tesseract(name);
  }

  Init(dataPath?: string, language: string = "eng") {
    return this._addonInstance.Init();
  }

  SetImage(image: any) {
    return this._addonInstance.SetImage(image);
  }

  greet(strName: string) {
    return this._addonInstance.greet(strName);
  }

  getUTF8Text() {
    return this._addonInstance.getUTF8Text();
  }

  // private members
  private _addonInstance: ITesseractNative;
}

export = Tesseract;
