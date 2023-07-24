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

-o, --outfile  
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
