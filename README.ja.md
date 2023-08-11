# rle

[English](./README.md) | [Japanese](./README.ja.md)  

## Name

enc - 入力されたpgm、ppm画像をランレングス圧縮
dec - ランレングス圧縮されたデータを展開

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
    出力するファイルの名前を指定します。  
    指定しなければ入力ファイル名で出力されます。  

## Usage

### Encode

```sh
./enc test.pgm
```

`test.pgm`が圧縮され、`test.rle`が生成されます。  

```sh
./enc -o output.rle input.ppm
```

`input.ppm`が圧縮され、`output.rle`が生成されます。  

### Decode

```sh
./dec test.rle
```

`test.rle`が展開され、`test.pmg`もしくは`test.ppm`が生成されます。  
出力フォーマットは入力ファイルから適切に選択されます。  

```sh
./dec -o output.ppm input.rle
```

`input.rle`が展開され、`output.ppm`が生成されます。  

## Build

```sh
make
```

カレントディレクトリに`enc`と`dec`が生成されます。  

## Benchmark Result

```txt
beta.pgm           766,793 bytes ->      9,690 bytes, 0.012637 ( 1.26%), OK
beta.ppm         2,661,393 bytes ->    998,952 bytes, 0.375349 (37.53%), OK
deer.ppm         4,575,324 bytes ->  1,302,352 bytes, 0.284647 (28.46%), OK
document.pgm       796,095 bytes ->     54,567 bytes, 0.068543 ( 6.85%), OK
eclipse.pgm      1,235,124 bytes ->    422,567 bytes, 0.342125 (34.21%), OK
fish.ppm         4,275,224 bytes ->  1,288,709 bytes, 0.301597 (30.16%), OK
hanabi.pgm       1,046,982 bytes ->    324,375 bytes, 0.309819 (30.98%), OK
hanabi.ppm       2,975,905 bytes ->  1,116,133 bytes, 0.375057 (37.51%), OK
ishigaki.pgm     1,226,223 bytes ->    360,440 bytes, 0.293943 (29.39%), OK
kiyomasa.pgm     1,180,126 bytes ->    332,159 bytes, 0.281461 (28.15%), OK
kiyomasa2.pgm      810,297 bytes ->    202,786 bytes, 0.250261 (25.03%), OK
kiyomasa2.ppm    2,407,515 bytes ->    857,881 bytes, 0.356335 (35.63%), OK
manual.pgm       1,734,016 bytes ->     66,474 bytes, 0.038335 ( 3.83%), OK
test.pgm               151 bytes ->         22 bytes, 0.145695 (14.57%), OK
test.ppm                64 bytes ->         32 bytes, 0.500000 (50.00%), OK
```
