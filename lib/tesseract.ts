const path = require("path");

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
  ProcessPages(
    imagePath: string,
    retryConfig: any,
    renderer: any,
    timeout: number
  ): boolean;
}

class Tesseract {
  constructor() {
    this._addonInstance = new addon.Tesseract();
  }

  Init(dataPath?: string, language: string = "eng") {
    let tessDataPath = dataPath;
    if (
      tessDataPath &&
      path.basename(path.dirname(tessDataPath)) === "@tessdata"
    ) {
      // tessDataPath = path.dirname(tessDataPath);
      console.log("the path 1", tessDataPath);
      console.log("the path 2", path.basename(tessDataPath));
    }
    return this._addonInstance.Init(tessDataPath, language);
  }

  SetImage(image: any) {
    return this._addonInstance.SetImage(image);
  }

  getUTF8Text() {
    return this._addonInstance.getUTF8Text();
  }

  ProcessPages({
    imagePath,
    retryConfig = null,
    timeout = 5000,
    renderer
  }: {
    imagePath: string;
    retryConfig?: any;
    timeout?: number;
    renderer: any;
  }) {
    return this._addonInstance.ProcessPages(
      imagePath,
      retryConfig,
      timeout,
      renderer
    );
  }

  // private members
  private _addonInstance: ITesseractNative;
}

export = Tesseract;
