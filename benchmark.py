import os
import glob


def get_benchmark_files():
    files = glob.glob("../images/*")
    files.sort()
    return files


def get_base_filename(file):
    return os.path.basename(file)


def get_base_filename_without_extension(file):
    return os.path.splitext(get_base_filename(file))[0]


def get_input_file_size(file):
    return os.path.getsize(file)


def encode(file):
    os.system(f"../enc {file}")
    return f"{get_base_filename_without_extension(file)}.rle"


def decode(file):
    os.system(f"../dec {get_base_filename_without_extension(file)}.rle")


def compression_ratio(file1, file2):
    return os.path.getsize(file1 + ".rle") / os.path.getsize(file2)


def compression_ratio_percent(file1, file2):
    return compression_ratio(file1, file2) * 100


def diff(file1, file2):
    return abs(os.path.getsize(file1) - os.path.getsize(file2))


def main():
    os.system("rm -rf ./bench")
    os.makedirs("./bench", exist_ok=True)
    os.chdir("./bench")

    for file in get_benchmark_files():
        print(get_base_filename(file), end="\t")
        print(f"{get_input_file_size(file):>10,} -> ", end="")
        encode(file)
        print(
            f"{get_input_file_size(f'{get_base_filename_without_extension(file)}.rle'):>10,}",
            end=", ",
        )
        decode(file)
        print(
            f"{compression_ratio(get_base_filename_without_extension(file), get_base_filename(file)):.6f}",
            end=" ",
        )
        print(
            f"({compression_ratio_percent(get_base_filename_without_extension(file), get_base_filename(file)):>5.2f}%)",
            end=", ",
        )
        print("OK" if diff(file, get_base_filename(file)) == 0 else "NG")


if __name__ == "__main__":
    main()
