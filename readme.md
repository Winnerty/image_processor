# Graphic filters (image_processor)

In this task I implemented a console application,
that allows you to apply various filters to images,
similar to filters in popular graphic editors.      


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


## Фильтры

В формулах далее считаем, что каждая компонента цвета
представлена вещественным числом от 0 до 1. Цвета пикселей
представлены тройками `(R, G, B)`. Таким образом, `(0, 0, 0)` – черный,
`(1, 1, 1)` – белый.

Если фильтр задан матрицей, это означает, что значение каждого из цветов определяется взвешенной суммой
значений этого цвета в соседних пикселях в соответствии с матрицей. При этом целевому пикселю
соответствует центральный элемент матрицы.

Например, для фильтра, заданного матрицей

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D1%20&%202%20&%203%20%5C%5C4%20&%205%20&%206%20%5C%5C7%20&%208%20&%209%20%5C%5C%5Cend%7Bbmatrix%7D)

Значение каждого из цветов целевого пикселя `C[x][y]` будет определяться формулой

```
C[x][y] =
  min(1, max(0,
   1*C[x-1][y-1] + 2*C[x][y-1] + 3*C[x+1][y-1] +
   4*C[x-1][y]   + 5*C[x][y]   + 6*C[x+1][y]   +
   7*C[x-1][y+1] + 8*C[x][y+1] + 9*C[x+1][y+1]
))
```

При обработке пикселей, близких к краю изображения, часть матрицы может выходить за границу изображения.
В таком случае в качестве значения пикселя, выходящего за границу, следует использовать значение ближайшего
к нему пикселя изображения.

### Список базовых фильтров

#### Crop (-crop width height)
Обрезает изображение до заданных ширины и высоты. Используется верхняя левая часть изображения.

Если запрошенные ширина или высота превышают размеры исходного изображения, выдается доступная часть изображения.

#### Grayscale (-gs)
Преобразует изображение в оттенки серого по формуле

![encoding](https://latex.codecogs.com/svg.image?R'%20=%20G'%20=%20B'%20=0.299%20R%20&plus;%200%20.587%20G%20&plus;%200%20.%20114%20B)

#### Negative (-neg)
Преобразует изображение в негатив по формуле

![encoding](https://latex.codecogs.com/svg.image?R'%20=%201%20-%20R,%20G'%20=%201%20-%20G,%20B'%20=%201%20-%20B)

#### Sharpening (-sharp)
Повышение резкости. Достигается применением матрицы

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%205%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

#### Edge Detection (-edge threshold)
Выделение границ. Изображение переводится в оттенки серого и применяется матрица

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%204%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

Пиксели со значением, превысившим `threshold`, окрашиваются в белый, остальные – в черный.

#### Gaussian Blur (-blur sigma)
[Гауссово размытие](https://ru.wikipedia.org/wiki/Размытие_по_Гауссу),
параметр – сигма.

Значение каждого из цветов пикселя `C[x0][y0]` определяется формулой

![encoding](https://latex.codecogs.com/svg.image?C%5Bx_0%5D%5By_0%5D%20%3D%20%5Csum_%7Bx%3D0%2Cy%3D0%7D%5E%7Bwidth-1%2C%20height-1%7DC%5Bx%5D%5By%5D%5Cfrac%7B1%7D%7B2%5Cpi%5Csigma%5E2%7De%5E%7B-%5Cfrac%7B%5Cleft%7Cx_o-x%5Cright%7C%5E2%20%26plus%3B%20%5Cleft%7Cy_o-y%5Cright%7C%5E2%7D%7B2%5Csigma%5E2%7D%7D)

Существуют различные варианты релализации и оптимизации вычисления этого фильтра, описание есть [в Википедии](https://ru.wikipedia.org/wiki/Размытие_по_Гауссу).

