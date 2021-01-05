NAME = space_invaders
CXX = gcc
OUT = obj

CFLAGS += `sdl2-config --cflags -g -fsanitize=address -fsanitize=undefined -Wall -Wextra -pedantic -Werror -lm -Wno-unused-variable -std=c99 -o3`
LDFLAGS += `sdl2-config --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer

vpath %.c %.h source
vpath %.h source

OBJS += main.o game.o use.o menu.o gameover.o

OBJ = $(patsubst %, $(OUT)/%, $(OBJS))

all: $(NAME)

$(OUT)/%.o: %.c %.h
	@mkdir -p $(OUT)
	$(CXX) $(CFLAGS) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OUT)/*.o $(NAME)