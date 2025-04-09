all: build

build: iny iny-not-overoptimized

iny: iny.c
	gcc -nostdlib -static -o iny iny.c -lc

iny-not-overoptimized: iny-not-overoptimized.c
	gcc -o iny-not-overoptimized.c iny-not-overoptimized.c.c

vi:
	vim \
		Makefile \
		iny.c \
		iny-not-overoptimized.c \
		README.md \

# Leave blank line above
