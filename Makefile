CC=cc
C_FILES=src/*.c
OUTPUT=bin/lispy

build: 
	$(CC) -std=c99 -Wall $(C_FILES) -ledit -lm -o $(OUTPUT)

run:
	$(OUTPUT)

clean:
	rm -rf bin/*

format:
	clang-format -i $(C_FILES)
