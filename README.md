# rle

[English](./README.md) | [Japanese](./README.ja.md)  

## Name

enc - Run-length compression of input pgm and ppm images  
dec - Decompression run-length compressed data  

## Synopsis

```sh
./enc [OPTION] FILE
```

```sh
./dec [OPTION] FILE
```

## Description

## Option

-o  
    Specify the name of the output file.  
    If not specified, the output will be the name of the input file.  

## Usage

### Encode

```sh
./enc test.pgm
```

The `test.pgm` is compressed and `test.rle` is generated.  

```sh
./enc -o output.rle input.ppm
```

The `input.ppm` is compressed and `output.rle` is generated.  

### Decode

```sh
./dec test.rle
```

The `test.rle` is expanded and `test.pmg` or `test.ppm` is generated.  
The output format is selected appropriately from the input files.  

```sh
./dec -o output.ppm input.rle
```

The `input.rle` is expanded and `output.ppm` is generated.  

## Build

```sh
make
```

The `enc` and `dec` are created in the current directory.  

## Benchmark Result

```txt
2021_beta.pgm              766,793 bytes ->      9,690 bytes, 0.012637 ( 1.26%), OK
2021_beta.ppm            2,661,393 bytes ->    998,952 bytes, 0.375349 (37.53%), OK
2021_deer.ppm            4,575,324 bytes ->  1,302,352 bytes, 0.284647 (28.46%), OK
2021_eclipse.pgm         1,235,124 bytes ->    422,567 bytes, 0.342125 (34.21%), OK
2021_fish.ppm            4,275,224 bytes ->  1,288,709 bytes, 0.301597 (30.16%), OK
2021_kiyomasa.pgm        1,180,126 bytes ->    332,159 bytes, 0.281461 (28.15%), OK
2021_manual.pgm          1,734,016 bytes ->     66,474 bytes, 0.038335 ( 3.83%), OK
2022_document.pgm          796,095 bytes ->     54,567 bytes, 0.068543 ( 6.85%), OK
2022_hanabi.pgm          1,046,982 bytes ->    324,375 bytes, 0.309819 (30.98%), OK
2022_hanabi.ppm          2,975,905 bytes ->  1,116,133 bytes, 0.375057 (37.51%), OK
2022_ishigaki.pgm        1,226,223 bytes ->    360,440 bytes, 0.293943 (29.39%), OK
2022_kiyomasa.pgm          810,297 bytes ->    202,786 bytes, 0.250261 (25.03%), OK
2022_kiyomasa.ppm        2,407,515 bytes ->    857,881 bytes, 0.356335 (35.63%), OK
2023_deer.ppm            3,488,360 bytes ->  1,335,923 bytes, 0.382966 (38.30%), OK
2023_eclipse.pgm         1,235,124 bytes ->    422,567 bytes, 0.342125 (34.21%), OK
2023_hanabi.pgm            811,694 bytes ->    206,256 bytes, 0.254106 (25.41%), OK
2023_hanabi.ppm          2,427,711 bytes ->  1,120,180 bytes, 0.461414 (46.14%), OK
2023_kiyomasa.pgm        1,180,126 bytes ->    332,159 bytes, 0.281461 (28.15%), OK
2023_oit.ppm             2,768,232 bytes ->    973,422 bytes, 0.351640 (35.16%), OK
2023_paper.pgm           1,141,447 bytes ->     95,268 bytes, 0.083462 ( 8.35%), OK
```
