var fs = require("fs");
var zlib = require("zlib");

// checks whether a file exists
function fileExists(filePath: string) {
  try {
    return fs.statSync(filePath).isFile();
  } catch (err) {
    return false;
  }
}

var gunzipFile = function(source: string, destination: string, callback?: any) {
  // check if source file exists
  console.log("FILE EXISTS", { fileExists: fileExists(source) });
  if (!fileExists(source)) {
    return false;
  }

  try {
    // prepare streams
    var src = fs.createReadStream(source);
    var dest = fs.createWriteStream(destination);

    // extract the archive
    src.pipe(zlib.createGunzip()).pipe(dest);

    // callback on extract completion
    dest.on("close", function() {
      if (typeof callback === "function") {
        callback();
      }
    });
  } catch (err) {
    // either source is not readable
    // or the destination is not writable
    // or file not a gzip
  }
};

export default gunzipFile;
