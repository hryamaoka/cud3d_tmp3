/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:25:06 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:25:07 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int valid_color(t_game *game) {
  if (game->ceiling.r <= 0 || game->ceiling.r >= 255)
    return (0);
  if (game->ceiling.g <= 0 || game->ceiling.g >= 255)
    return (0);
  if (game->ceiling.b <= 0 || game->ceiling.b >= 255)
    return (0);
  if (game->floor.r <= 0 || game->floor.r >= 255)
    return (0);
  if (game->floor.g <= 0 || game->floor.g >= 255)
    return (0);
  if (game->floor.b <= 0 || game->floor.b >= 255)
    return (0);
  return (1);
}
