/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:25:44 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:25:45 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "ft_printf.h"
#include "get_next_line.h"

#include "libft.h"
#include "mlx.h"

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_tex {
  char *no;
  char *so;
  char *we;
  char *ea;
} t_tex;

typedef struct s_color {
  int r;
  int g;
  int b;
} t_color;

typedef struct s_map {
  char **grid;
  int width;
  int height;
} t_map;

typedef struct s_player {
  double x;
  double y;
  double dir_x;
  double dir_y;
  double plane_x;
  double plane_y;
  char direction;
} t_player;

typedef struct s_ray {
  double camera_x;
  double ray_dir_x;
  double ray_dir_y;
  int map_x;
  int map_y;
  double side_dist_x;
  double side_dist_y;
  double delta_dist_x;
  double delta_dist_y;
  double perp_wall_dist;
  int step_x;
  int step_y;
  int hit;
  int side;
  int line_height;
  int draw_start;
  int draw_end;
} t_ray;

typedef struct s_img {
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
  int width;
  int height;
} t_img;

typedef struct s_sprite {
  double x;
  double y;
} t_sprite;

typedef struct s_game {
  void *mlx;
  void *win;

  t_img img;

  t_tex tex;

  t_img wall_tex[4];
  t_img door_tex;
  t_img sprite_tex[2];

  t_color floor;
  t_color ceiling;
  t_map map;
  t_player player;
  t_ray ray;

  double *z_buffer;
  int num_sprites;
  t_sprite *sprites;
  int frame_count;
} t_game;

void init_game(t_game *game);

int check_filename(char *filename);

void free_split(char **split);
void free_all(t_game *game);

void perror_and_exit(char *msg, t_game *game);

void parse(char *filename, t_game *game);

int init_window(t_game *game);
int close_game(t_game *game);
int key_press(int keycode, t_game *game);
int mouse_handler(int x, int y, t_game *game);

int render_frame(t_game *game);
void raycast(t_game *game);

int init_textures(t_game *game);
unsigned int get_texture_color(t_img *tex, int x, int y);

void init_sprites(t_game *game);

#endif
