
# Определение системных команд
NAME = sprite_test

# Флаги компиляции:
GCC = gcc -O3
CCFLAGS = -Wall -Wextra
OTHERS_FLAGS = -lm

# Список фреймворков и их пути:
FRAME_SDL2_DIR = Frameworks
FRAME_SDL2 = $(FRAME_SDL2_DIR)/SDL2.framework
FRAME_SDL2_IMAGE = $(FRAME_SDL2_DIR)/SDL2_image.framework
FRAME_SDL2_MIXER = $(FRAME_SDL2_DIR)/SDL2_mixer.framework
FRAMEWORKS = -F Frameworks \
	-framework SDL2 \
	-framework SDL2_image \
	-framework SDL2_mixer \
	-rpath $(FRAME_SDL2_DIR)

# Список библиотек и их пути:
LIBFT_DIRECTORY = libft
LIBFT_NAME = $(LIBFT_DIRECTORY)/libft.a

# Флаги для сборки библиотек
LIBRARIES_LIBFT = -L $(LIBFT_DIRECTORY) -lft

# Заголовочные файлы и их пути:
INCLUDES_DIRECTORY = includes/
INCLUDES_DIRECTORY_LIBFT = $(LIBFT_DIRECTORY)/includes
INCLUDES_SDL2 = -F $(FRAME_SDL2_DIR) \
	-I $(FRAME_SDL2)/Headers \
	-I $(FRAME_SDL2_IMAGE)/Headers \
	-I $(FRAME_SDL2_MIXER)/Headers

INCLUDES = -I$(INCLUDES_DIRECTORY) \
	-I$(INCLUDES_DIRECTORY_LIBFT) \
	$(INCLUDES_SDL2)

HEADERS_LIST = *.h

HEADERS = $(addprefix $(INCLUDES_DIRECTORY), $(HEADERS_LIST))

# Основные файлы программы и их пути:
SRC_DIRECTORY = src/
SRC_LIST = calc_quads.c \
		draw_door.c \
		draw_room.c \
		draw_ui.c \
		enemies.c \
		player.c \
		props.c \
		wad/blit_sprite_scale.c \
		wad/bytes_shift.c \
		wad/debug_file.c \
		wad/draw_hud.c \
		wad/draw_sprite.c \
		wad/draw_texture.c \
		wad/draw_wad.c \
		wad/fill_functions.c \
		wad/init_hud.c \
		wad/init_wad.c \
		wad/struct_timer.c \
		wad/timer.c \
		wad/wad_get.c \
		wad/wad_loader.c \
		wad/wad_main_menu.c \
		wad/wad_reader.c \
		wad/wad_sprite.c \
		wad/acces_pixel.c \
		wolf3d.c

SRC = $(addprefix $(SRC_DIRECTORY), $(SRC_LIST))

OBJECTS_DIRECTORY = obj/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# Определение цвета вывода:
GREEN = \033[0;32;1m
RED = \033[0;31;1m
RESET = \033[0m

# Лабуда-бу-даб-даб
.PHONY: all clean fclean re

# Основные правила сборки:
all: $(LIBFT_NAME) $(NAME)

$(NAME): $(SRC) $(HEADERS)
	@echo "wolf3d: $(GREEN)Компиляция исполняемого файла$(RESET)\n"
	@$(GCC) $(CCFLAGS) $(INCLUDES) $(LIBRARIES_LIBFT) $(FRAMEWORKS) $(OTHERS_FLAGS) $(SRC) -o $(NAME)
	@echo "wolf3d: $(GREEN)Компиляция завершена$(RESET)\n"

$(LIBFT_NAME):
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

debug: $(LIBFT_DIRECTORY) $(SRC) $(HEADERS)
	@$(MAKE) -sC $(LIBFT_DIRECTORY)
	@echo "wolf3d: $(GREEN)Компиляция исполняемого файла$(RESET)\n"
	@$(GCC) -g $(CCFLAGS) $(INCLUDES) $(LIBRARIES_LIBFT) $(FRAMEWORKS) $(OTHERS_FLAGS) $(SRC) -o $(NAME)
	@echo "wolf3d: $(GREEN)Компиляция завершена$(RESET)\n"

clean:
	@$(MAKE) -C $(LIBFT_DIRECTORY) clean

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)Исполняемый файл $(NAME) удален$(RESET)\n"
	@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean

re:
	@$(MAKE) fclean
	@$(MAKE) all
