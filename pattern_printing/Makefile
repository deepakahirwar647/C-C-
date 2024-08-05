# Define the compiler
CC = gcc

# Define the target executables and their sources
TARGETS = 01_sine_pattern.exe 02_sine_pattern.exe 03_sine_pattern.exe 04_cosine_pattern.exe
SOURCES = 01_sine_pattern.c 02_sine_pattern.c 03_sine_pattern.c 04_cosine_pattern.c

# Default target to build all executables
all: $(TARGETS)

# Rules to build each executable
01_sine_pattern.exe: 01_sine_pattern.c
	$(CC) 01_sine_pattern.c -o 01_sine_pattern.exe

02_sine_pattern.exe: 02_sine_pattern.c
	$(CC) 02_sine_pattern.c -o 02_sine_pattern.exe

03_sine_pattern.exe: 03_sine_pattern.c
	$(CC) 03_sine_pattern.c -o 03_sine_pattern.exe

04_cosine_pattern.exe: 04_cosine_pattern.c
	$(CC) 04_cosine_pattern.c -o 04_cosine_pattern.exe

# Clean rule to remove all executables
clean:
	rm -f $(TARGETS)
