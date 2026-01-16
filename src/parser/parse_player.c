/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:24:42 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:24:43 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void set_direction(t_game *game) {
  if (game->player.direction == 'N') {
    game->player.dir_x = 0;
    game->player.dir_y = -1;
    game->player.plane_x = 0.66;
    game->player.plane_y = 0;
  } else if (game->player.direction == 'S') {
    game->player.dir_x = 0;
    game->player.dir_y = 1;
    game->player.plane_x = -0.66;
    game->player.plane_y = 0;
  } else if (game->player.direction == 'W') {
    game->player.dir_x = -1;
    game->player.dir_y = 0;
    game->player.plane_x = 0;
    game->player.plane_y = -0.66;
  } else if (game->player.direction == 'E') {
    game->player.dir_x = 1;
    game->player.dir_y = 0;
    game->player.plane_x = 0;
    game->player.plane_y = 0.66;
  } else
    return;
}

static void set_player_info(t_game *game, int x, int y, char dir) {
  game->player.x = x + 0.5;
  game->player.y = y + 0.5;
  game->player.direction = dir;
  set_direction(game);
}

int find_player(t_game *game) {
  int y;
  int x;
  int count;

  count = 0;
  y = 0;
  while (game->map.grid[y]) {
    x = 0;
    while (game->map.grid[y][x]) {
      if (ft_strchr("NSWE", game->map.grid[y][x])) {
        count++;
        set_player_info(game, x, y, game->map.grid[y][x]);
      }
      x++;
    }
    y++;
  }
  if (count != 1)
    return (0);
  return (1);
}
