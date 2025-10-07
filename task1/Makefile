.PHONY: all build check clean

CFLAGS=-Wall -Wextra -Wpedantic -Werror

all: build check

build:
	${CC} ${CFLAGS} -o my-wc main.c

check: build
	@${CC} ${CFLAGS} -o tests/test tests/test.c
	@tests/test || { echo "ERROR: Tests are failing!"; exit 1; }

clean:
	${RM} my-wc tests/test
