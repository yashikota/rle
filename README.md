# rle

[English](./README.md) | [Japanese](./README.ja.md)  

## Name

enc - Run-length compression of input pgm and ppm images  
dec - Decompress run-length compressed data  

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
