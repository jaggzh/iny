all: build

build: iny iny-raw

iny-raw: iny-raw.c
	gcc -nostdlib -static -o iny-raw iny-raw.c -lc

iny: iny.c
	gcc -o iny iny.c

vi:
	vim \
		Makefile \
		iny.c \
		iny-raw.c \
		tests/test-timing \
		README.md \

# Leave blank line above
