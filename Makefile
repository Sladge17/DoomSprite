NAME = sprite_test
# FLAG = -Wall -Wextra -Werror
FLAG = -g -O2

HEADER_DIR = includes/
HEADER_DIR_WAD = src/wad/$(HEADER_WAD)
HEADER_WAD = include_wad/
HEADER = -I $(HEADER_DIR) -I $(HEADER_DIR_WAD) -I $(LIBFT_DIR)

SRC_DIR = src/
SRC_LIST =	wolf3d.c \
			draw_room.c \
			calc_quads.c \
			player.c \
			enemies.c \
			props.c \
			draw_ui.c \
			draw_door.c \
			wad/src_wad/acces_pixel.c \
			wad/src_wad/blit_sprite_scale.c \
			wad/src_wad/blit_surf_scale.c \
			wad/src_wad/debug_file.c \
			wad/src_wad/main.c \
			wad/src_wad/bytes_shift.c \
			wad/src_wad/draw_sprite.c \
			wad/src_wad/draw_texture.c \
			wad/src_wad/draw_wad.c \
			wad/src_wad/wad_get.c \
			wad/src_wad/wad_loader.c \
			wad/src_wad/wad_reader.c

# SRC_LIST = wolf2.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# LIBFT_DIR = LibFT/
# LIBFT = $(LIBFT_DIR)libft.a

LIBFT_DIR = LibFT/
LIBFT = -L $(LIBFT_DIR) -lft

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
	@gcc -o $(NAME) $(OBJ) $(LIBFT) $(SDL)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)*.h
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)wad
	@mkdir -p $(OBJ_DIR)wad/src_wad
	@gcc -c $(HEADER) $(SDL_HEADER) $< -o $@ $(FLAG)

clean:
	@rm -rf $(OBJ_DIR)
	# @make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	# @make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
