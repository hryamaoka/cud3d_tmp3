#ifndef RENDER_INTERNAL_H
#define RENDER_INTERNAL_H

#include "cub3d.h"

#define MM_SCALE 12
#define MM_COLOR_WALL 0xFFFFFF
#define MM_COLOR_PLAYER 0xFF0000
#define MM_COLOR_FLOOR 0x000000
#define MM_OFFSET_X 10
#define MM_OFFSET_Y 10

void select_texture(t_game *game, t_img **tex);
void sort_sprites(int *order, double *dist, int amount);

typedef struct s_sprite_vars {
  double transform_y;
  int sprite_screen_x;
  int sprite_height;
  int sprite_width;
  int draw_start_x;
  int draw_end_x;
  int draw_start_y;
  int draw_end_y;
  t_img *tex;
} t_sprite_vars;

void setup_sprite_vars(t_game *game, int i, int *order, t_sprite_vars *vars);
void draw_stripe(t_game *game, t_sprite_vars *vars, int stripe);
void draw_textured_line(t_game *game, int x, int *draw, t_img *tex, int tex_x);
void draw_floor_ceiling(t_game *game, int x, int draw_start, int draw_end);
void draw_minimap(t_game *game);
void draw_sprites(t_game *game);

#endif
