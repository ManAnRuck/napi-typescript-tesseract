import { basename, dirname } from "path";

let addon: any;
var fs = require("fs");
if (fs.existsSync("../build/Release")) {
  addon = require("../build/Release/tesseract-native");
} else {
  addon = require("../build/Debug/tesseract-native");
}

class PdfRenderer {
  constructor({
    outputBase,
    dataPath = `${dirname(__dirname)}/`,
    textOnly = false
  }: {
    outputBase: string;
    dataPath?: string;
    textOnly?: boolean;
  }) {
    return new addon.PdfRenderer(outputBase, dataPath, textOnly);
  }
}

export = PdfRenderer;
