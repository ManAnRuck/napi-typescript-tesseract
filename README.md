# napi-typescript-tesseract

not on npm now (comming soon), but u can localy link.

1. clone project
2. cd napi-typescript-tesseract
3. `yarn link`
4. go to your project
5. `yarn link napi-typescript-tesseract`

### Usage

```js
    const tesseract = new Tesseract();
    tesseract.Init(null, "eng");

    const image = new Image(`${__dirname}/image.png`)
    console.log(image)

    tesseract.SetImage(image);
    console.log(tesseract.getUTF8Text());
```
