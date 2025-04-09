all: build tests

build: iny iny-raw

tests: build
	tests/test-functional

iny-raw: iny-raw.c
	gcc -nostdlib -static -o iny-raw iny-raw.c -lc

iny: iny.c
	gcc -o iny iny.c

vi:
	vim \
		Makefile \
		iny.c \
		iny-raw.c \
		tests/test-functional \
		tests/test-timing \
		README.md \

# Leave blank line above
