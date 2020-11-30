NAME = sprite_test
# FLAG = -Wall -Wextra -Werror
FLAG = -g

HEADER_DIR = includes/
HEADER = -I $(HEADER_DIR)

SRC_DIR = src/
SRC_LIST =	wolf3d.c \
			draw_room.c \
			calc_quads.c \
			draw_sprite.c \
			player.c \
			enemies.c \
			props.c \
			draw_ui.c \
			draw_door.c
# SRC_LIST = wolf2.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

LIBFT_DIR = LibFT/
LIBFT = $(LIBFT_DIR)libft.a

# SDL = -L sdl/lib/ -lSDL2 -lSDL2_image
# SDL_HEADER = -I sdl/include/SDL2

SDL = -F Frameworks\
	-framework SDL2\
	-framework SDL2_image\
	-framework SDL2_mixer\
	-rpath Frameworks

SDL_HEADER = -F Frameworks\
			-I Frameworks/SDL2.framework/Headers\
			-I Frameworks/SDL2_image.framework/Headers\
			-I Frameworks/SDL2_mixer.framework/Headers

all: $(NAME)

$(NAME): $(OBJ)
	# @make re -C $(LIBFT_DIR)
	# gcc -o wolf -I includes src/*.c -Wall -Wextra -Werror -L sdl/lib/ -I sdl/include/SDL2 -lSDL2
	gcc -o $(NAME) $(OBJ) $(LIBFT) $(SDL)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)*.h
	mkdir -p $(OBJ_DIR)
	gcc -c $(HEADER) $(SDL_HEADER) $< -o $@ $(FLAG)

clean:
	@rm -rf $(OBJ_DIR)
	# @make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	# @make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
