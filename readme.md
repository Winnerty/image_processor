# Graphic filters (image_processor)

In this task I implemented a console application,
that allows you to apply various filters to images,
similar to filters in popular graphic editors.  
<br>

## Supported image format

Input and output graphic files should be in [BMP](http://en.wikipedia.org/wiki/BMP_file_format) format.

BMP format supports quite a few variations, but in this task we will use
24-bit BMP with no compression and no color table. The type of `DIB header` used is `BITMAPINFOHEADER`.

There is an example of a file in the required format in the Wikipedia article [under "Example 1"](https://en.wikipedia.org/wiki/BMP_file_format#Example_1).
and in the [test_script/data](test_script/data) folder.

When testing, make sure that the test image
should be saved in 24-bit BMP.


## Command line argument format

Command line argument format description:

`{program name} {path to input file} {path to output file}
[-{filter name 1} [filter parameter 1] [filter parameter 2] ...]
[-{filter name 2} [filter parameter 1] [filter parameter 2] ...] ...] ...`

When run without arguments, the program displays help.

### Example
`./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5`

In this example.
1. Loads the image from the `input.bmp` file
2. it is cropped to an image with the start in the upper left corner and size 800x600 pixels
3. Converted to grayscale
4. Blur with sigma 0.5 is applied
5. The resulting image is saved to the `/tmp/output.bmp` file

The filter list can be empty, then the image must be saved as is.
Filters are applied in the order in which they are listed in the command line arguments.    


## Filters

In the formulas below, we assume that each component of color
is represented by a real number from 0 to 1. Pixel colors
are represented by the triples `(R, G, B)`. Thus, `(0, 0, 0, 0)` is black,
`(1, 1, 1, 1)` is white.

If the filter is given by a matrix, this means that the value of each color is determined by the weighted sum of the
values of this color in neighboring pixels according to the matrix. In this case, the target pixel
corresponds to the center element of the matrix.

For example, for the filter defined by the matrix

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D1%20&%202%20&%203%20%5C%5C4%20&%205%20&%206%20%5C%5C7%20&%208%20&%209%20%5C%5C%5Cend%7Bbmatrix%7D)

The value of each of the colors of the target pixel `C[x][y]` will be determined by the formula


```
C[x][y] =
  min(1, max(0,
   1*C[x-1][y-1] + 2*C[x][y-1] + 3*C[x+1][y-1] +
   4*C[x-1][y]   + 5*C[x][y]   + 6*C[x+1][y]   +
   7*C[x-1][y+1] + 8*C[x][y+1] + 9*C[x+1][y+1]
))
```

When processing pixels close to the edge of the image, part of the matrix may extend beyond the image boundary.
In such a case, the value of the nearest image pixel should be used as the value of the pixel that is outside the boundary.
pixel value should be used as the value of the nearest pixel in the image.

### List of basic filters

#### Crop (-crop width height)
Crop the image to the specified width and height. The upper left portion of the image is used.

If the requested width or height exceeds the dimensions of the original image, the available portion of the image is output.  
<br>

#### Grayscale (-gs)
Converts the image to grayscale using the formula

![encoding](https://latex.codecogs.com/svg.image?R'%20=%20G'%20=%20B'%20=0.299%20R%20&plus;%200%20.587%20G%20&plus;%200%20.%20114%20B)  
<br>

#### Negative (-neg)
Converts the image to negative using the formula

![encoding](https://latex.codecogs.com/svg.image?R'%20=%201%20-%20R,%20G'%20=%201%20-%20G,%20B'%20=%201%20-%20B)  
<br>

#### Sharpening (-sharp)
Sharpening. Achieved by applying a matrix

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%205%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)  
<br>

#### Edge Detection (-edge threshold)
Edge detection. The image is converted to grayscale and matrix is applied

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%204%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

Pixels with value exceeding `threshold` are colored white, the rest - black.  
<br>

#### Gaussian Blur (-blur sigma)
[Gaussian Blur](https://en.wikipedia.org/wiki/Gaussian_blur),
the parameter is sigma.

The value of each of the pixel colors `C[x0][y0]` is determined by the formula

![encoding](https://latex.codecogs.com/svg.image?C%5Bx_0%5D%5By_0%5D%20%3D%20%5Csum_%7Bx%3D0%2Cy%3D0%7D%5E%7Bwidth-1%2C%20height-1%7DC%5Bx%5D%5By%5D%5Cfrac%7B1%7D%7B2%5Cpi%5Csigma%5E2%7De%5E%7B-%5Cfrac%7B%5Cleft%7Cx_o-x%5Cright%7C%5E2%20%26plus%3B%20%5Cleft%7Cy_o-y%5Cright%7C%5E2%7D%7B2%5Csigma%5E2%7D%7D)

There are different variants of relalization and optimization of this filter calculation, there is a description [in Wikipedia](https://en.wikipedia.org/wiki/Gaussian_blur).

