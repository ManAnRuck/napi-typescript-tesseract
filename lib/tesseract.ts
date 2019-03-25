import { dirname, basename } from "path";
import gunzip from "./gunzip";
import Image = require("./image");

const buildType = require("fs")
  .readdirSync(require("path").join(dirname(dirname(__dirname)), "build"))
  .filter((item: string) => item === "Debug" || item === "Release")[0];

const addon = require(`../../build/${buildType}/tesseract-native`);

interface ITesseractNative {
  Init(dataPath?: string, language?: string): void;
  SetImage(image: Image): void;
  getUTF8Text(): string;
  End(): void;
  ProcessPages(
    imagePath: string,
    retryConfig: any,
    renderer: any,
    timeout: number
  ): boolean;
  ProcessPage(
    image: Image,
    pageIndex: number,
    imagePath: string,
    retryConfig: any,
    timeout: number,
    renderer: any
  ): boolean;
}

class Tesseract {
  constructor() {
    this._addonInstance = new addon.Tesseract();
  }

  Init(dataPath?: string, language: string = "eng") {
    let tessDataPath = dataPath;
    if (tessDataPath && basename(dirname(tessDataPath)) === "@tessdata") {
      // tessDataPath = dirname(tessDataPath);
      console.log("the path 1", tessDataPath);
      console.log("the path 2", basename(tessDataPath));
      console.log("the path 3", `${tessDataPath}/deu.traineddata.gz`);
      gunzip(
        `${tessDataPath}/deu.traineddata.gz`,
        `${tessDataPath}/deu.traineddata`
      );
    }
    return this._addonInstance.Init(tessDataPath, language);
  }

  SetImage(image: Image) {
    return this._addonInstance.SetImage(image);
  }

  getUTF8Text() {
    return this._addonInstance.getUTF8Text();
  }

  End() {
    return this._addonInstance.End();
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

  ProcessPage({
    image,
    pageIndex,
    imagePath,
    retryConfig = null,
    timeout = 5000,
    renderer
  }: {
    image: Image;
    pageIndex: number;
    imagePath: string;
    retryConfig?: any;
    timeout?: number;
    renderer: any;
  }) {
    return this._addonInstance.ProcessPage(
      image,
      pageIndex,
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
