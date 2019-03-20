import { dirname } from "path";

const buildType = require("fs")
  .readdirSync(require("path").join(dirname(dirname(__dirname)), "build"))
  .filter((item: string) => item === "Debug" || item === "Release")[0];

const addon = require(`../../build/${buildType}/tesseract-native`);

class Image {
  constructor(filePath: string) {
    return new addon.Image(filePath);
  }
}

export = Image;
