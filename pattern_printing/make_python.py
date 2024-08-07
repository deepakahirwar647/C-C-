"""Creates a simple makefile for all the c files in directory"""

from pathlib import Path
import os

script_dir = Path(__file__).resolve().parent
MAKE_PATH = script_dir / "Makefile"


def main():
    c_files: list[tuple[str, str]] = []
    try:
        for file in os.listdir(script_dir):
            if file.endswith(".c"):
                filename, _ = file.split(".")
                files = f"{filename}.c", f"{filename}.exe"
                c_files.append(files)
        c_files.sort(key=lambda strings: compare(strings[0]))
        make(c_files)
    except Exception as e:
        print(f"An error occured while processing files: {e}")


def compare(s: str) -> str:
    """If s starswith single digit then pads 0 at start"""
    if s[0].isdigit() and not s[1].isdigit():
        return "0" + s
    else:
        return s


def make(c_files: list[tuple[str, str]]):
    """Generate a Makefile for the given list of C source and executable files."""
    try:
        with open(MAKE_PATH, "w") as f:
            targets = " ".join([exe_file for _, exe_file in c_files])
            sources = " ".join([c_file for c_file, _ in c_files])

            print("# Define the compiler", file=f)
            print("CC = gcc\n", file=f)

            print("# Define the target executables and their sources", file=f)
            print(f"TARGETS = {targets}", file=f)
            print(f"SOURCES = {sources}\n", file=f)

            print("# Default target to build all executables", file=f)
            print(f"all: $(TARGETS)\n", file=f)

            print("# Rules to build each executable", file=f)
            for c_file, exe_file in c_files:
                print(f"{exe_file}: {c_file}", file=f)
                print(f"\t$(CC) {c_file} -o {exe_file}\n", file=f)

            print("# Clean rule to remove all executables", file=f)
            print("clean:", file=f)
            print(f"\trm -f $(TARGETS)", file=f)

        print("Makefile created successfully.")
    except Exception as e:
        print(f"An error occured while creating the Makefile: {e}")


if __name__ == "__main__":
    main()
