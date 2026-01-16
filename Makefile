# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/16 14:25:52 by hyamaoka          #+#    #+#              #
#    Updated: 2026/01/16 14:25:53 by hyamaoka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wextra -Wall -Werror -g
RM = rm -rf

SRC_DIR = ./src
INC_DIR = ./include
LIB_DIR = ./libft

SRC = src/main.c \
	src/core/game_init.c src/core/window.c src/core/game_cleanup.c src/core/error.c \
	src/parser/check_file.c src/parser/parse_main.c src/parser/parse_map.c src/parser/parse_map_utils.c \
	src/parser/parse_textures.c src/parser/parse_colors.c src/parser/textures_init.c \
	src/parser/parse_player.c src/parser/parse_utils.c src/parser/valid.c src/parser/valid_map.c \
	src/input/movement.c src/input/action.c src/input/rotate.c \
	src/utils/utils.c \
	src/engine/raycast.c src/engine/raycast_utils.c \
	src/render/sprite.c src/render/render.c src/render/sprite_utils.c src/render/minimap.c

OBJS = $(SRC:.c=.o)

LIBFT = $(LIB_DIR)/libft.a

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    # MacOS
    MLX_DIR = ./minilibx_opengl_20191021
    MLX = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
    # Linux
    MLX_DIR = ./minilibx-linux
    MLX = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

INCLUDES = -I$(INC_DIR) -I$(LIB_DIR)/includes -I$(MLX_DIR) \
           -Isrc/core -Isrc/parser -Isrc/engine -Isrc/render -Isrc/input -Isrc/utils

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(NAME)	

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
