/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:22:56 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:22:56 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game(t_game *game) {
  ft_bzero(game, sizeof(t_game));
  game->floor.r = -1;
  game->floor.g = -1;
  game->floor.b = -1;
  game->ceiling.r = -1;
  game->ceiling.g = -1;
  game->ceiling.b = -1;
  game->map.width = -1;
  game->map.height = -1;
  game->player.x = -1;
  game->player.y = -1;
  game->player.dir_x = -1;
  game->player.dir_y = -1;
}
