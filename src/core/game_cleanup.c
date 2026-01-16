/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:34:24 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/13 15:34:25 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_split(char **split) {
  int i;

  i = 0;
  if (!split)
    return;
  while (split[i])
    free(split[i++]);
  free(split);
}

void free_all(t_game *game) {
  if (game->tex.no)
    free(game->tex.no);
  if (game->tex.so)
    free(game->tex.so);
  if (game->tex.we)
    free(game->tex.we);
  if (game->tex.ea)
    free(game->tex.ea);
  if (game->map.grid)
    free_split(game->map.grid);
  if (game->z_buffer)
    free(game->z_buffer);
  if (game->sprites)
    free(game->sprites);
  if (game->mlx) {
    int i = 0;
    while (i < 4) {
      if (game->wall_tex[i].img)
        mlx_destroy_image(game->mlx, game->wall_tex[i].img);
      i++;
    }
    if (game->door_tex.img)
      mlx_destroy_image(game->mlx, game->door_tex.img);
    if (game->sprite_tex[0].img)
      mlx_destroy_image(game->mlx, game->sprite_tex[0].img);
    if (game->sprite_tex[1].img)
      mlx_destroy_image(game->mlx, game->sprite_tex[1].img);

    if (game->img.img)
      mlx_destroy_image(game->mlx, game->img.img);
    if (game->win)
      mlx_destroy_window(game->mlx, game->win);

    mlx_destroy_display(game->mlx);
    free(game->mlx);
  }
}
