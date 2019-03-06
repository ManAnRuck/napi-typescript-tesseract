const addon = require("../build/Release/tesseract-native");

interface ITesseractNative {
  Init(): void;
  SetImage(): void;
  greet(strName: string): string;
  getUTF8Text(): string;
}

class Tesseract {
  constructor(name: string) {
    this._addonInstance = new addon.Tesseract(name);
  }

  Init() {
    return this._addonInstance.Init();
  }

  SetImage() {
    return this._addonInstance.SetImage();
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
