/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:25:19 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:25:19 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"

void sort_sprites(int *order, double *dist, int amount) {
  int i;
  int j;
  double tmp_dist;
  int tmp_order;

  i = 0;
  while (i < amount - 1) {
    j = 0;
    while (j < amount - i - 1) {
      if (dist[j] < dist[j + 1]) {
        tmp_dist = dist[j];
        dist[j] = dist[j + 1];
        dist[j + 1] = tmp_dist;
        tmp_order = order[j];
        order[j] = order[j + 1];
        order[j + 1] = tmp_order;
      }
      j++;
    }
    i++;
  }
}

void setup_sprite_vars(t_game *game, int i, int *order, t_sprite_vars *vars) {
  double sprite_x;
  double sprite_y;
  double inv_det;
  double transform_x;

  sprite_x = game->sprites[order[i]].x - game->player.x;
  sprite_y = game->sprites[order[i]].y - game->player.y;
  inv_det = 1.0 / (game->player.plane_x * game->player.dir_y -
                   game->player.dir_x * game->player.plane_y);
  transform_x =
      inv_det * (game->player.dir_y * sprite_x - game->player.dir_x * sprite_y);
  vars->transform_y = inv_det * (-game->player.plane_y * sprite_x +
                                 game->player.plane_x * sprite_y);
  vars->sprite_screen_x =
      (int)((game->img.width / 2) * (1 + transform_x / vars->transform_y));
  vars->sprite_height = ft_abs((int)(game->img.height / (vars->transform_y)));
  vars->draw_start_y = -vars->sprite_height / 2 + game->img.height / 2;
  if (vars->draw_start_y < 0)
    vars->draw_start_y = 0;
  vars->draw_end_y = vars->sprite_height / 2 + game->img.height / 2;
  if (vars->draw_end_y >= game->img.height)
    vars->draw_end_y = game->img.height - 1;
  vars->sprite_width = ft_abs((int)(game->img.height / (vars->transform_y)));
  vars->draw_start_x = -vars->sprite_width / 2 + vars->sprite_screen_x;
  if (vars->draw_start_x < 0)
    vars->draw_start_x = 0;
  vars->draw_end_x = vars->sprite_width / 2 + vars->sprite_screen_x;
  if (vars->draw_end_x >= game->img.width)
    vars->draw_end_x = game->img.width - 1;
  vars->tex = &game->sprite_tex[(game->frame_count / 10) % 2];
}

static void draw_stripe_pixels(t_game *game, t_sprite_vars *vars, int stripe) {
  int y;
  int d;
  int tex_y;
  unsigned int color;
  int tex_x;

  tex_x =
      (int)(256 * (stripe - (-vars->sprite_width / 2 + vars->sprite_screen_x)) *
            vars->tex->width / vars->sprite_width) /
      256;
  y = vars->draw_start_y;
  while (y < vars->draw_end_y) {
    d = (y) * 256 - game->img.height * 128 + vars->sprite_height * 128;
    tex_y = ((d * vars->tex->height) / vars->sprite_height) / 256;
    color = get_texture_color(vars->tex, tex_x, tex_y);
    if ((color & 0x00FFFFFF) != 0) {
      int pixel = (y * game->img.line_length) +
                  (stripe * (game->img.bits_per_pixel / 8));
      game->img.addr[pixel] = color & 0xFF;
      game->img.addr[pixel + 1] = (color >> 8) & 0xFF;
      game->img.addr[pixel + 2] = (color >> 16) & 0xFF;
    }
    y++;
  }
}

void draw_stripe(t_game *game, t_sprite_vars *vars, int stripe) {
  if (vars->transform_y > 0 && stripe > 0 && stripe < game->img.width &&
      vars->transform_y < game->z_buffer[stripe]) {
    draw_stripe_pixels(game, vars, stripe);
  }
}
