# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -W -Werror -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS =`pkg-config --libs sdl` -lSDL_image

OBJ = main.o pixel_operations.o image_operations.o
DEP = ${OBJ:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} main

-include ${DEP}

# END
