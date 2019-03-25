# napi-typescript-tesseract

not on npm now (comming soon), but u can localy link.

1. clone project
2. cd napi-typescript-tesseract
3. `yarn link`
4. go to your project
5. `yarn link napi-typescript-tesseract`

### Usage

get text

```js
import { Tesseract, Image } from "napi-typescript-tesseract";

const tesseract = new Tesseract();
tesseract.Init(null, "eng");

const image = new Image(`${__dirname}/image.png`);
console.log(image);

tesseract.SetImage(image);
console.log(tesseract.getUTF8Text());
tesseract.End();
```

get searchable pdf (multipage)

```js
const tesseract = new Tesseract();
tesseract.Init(langPath, "deu");
const pdfRenderer = new PdfRenderer({
  outputBase: "test_pdf_multi"
});
const image = new Image(`${__dirname}/image.png`);
tesseract.ProcessPage({
  image,
  pageIndex: 0,
  imagePath: `${__dirname}/image.png`,
  renderer: pdfRenderer
});
const image2 = new Image(`${__dirname}/image.png`);
tesseract.ProcessPage({
  image: image2,
  pageIndex: 1,
  imagePath: `${__dirname}/image.png`,
  renderer: pdfRenderer
});
pdfRenderer.EndDocument();
tesseract.End();
```
