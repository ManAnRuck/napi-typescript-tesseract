import { dirname } from "path";

const buildType = require("fs")
  .readdirSync(require("path").join(dirname(dirname(__dirname)), "build"))
  .filter((item: string) => item === "Debug" || item === "Release")[0];

const addon = require(`../../build/${buildType}/tesseract-native`);

class PdfRenderer {
  constructor({
    outputBase,
    dataPath = `${dirname(dirname(__dirname))}/`,
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
