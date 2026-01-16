/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:54:23 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 13:23:20 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char *argv[]) {
  t_game game;

  if (argc != 2)
    perror_and_exit("usage: ./cub3d <map.cub>", NULL);
  if (!check_filename(argv[1]))
    perror_and_exit("usage: ./cub3d <map.cub>", NULL);
  init_game(&game);
  parse(argv[1], &game);
  if (!init_window(&game))
    perror_and_exit("Could not initialize window", &game);
  if (!init_textures(&game))
    perror_and_exit("Could not load textures", &game);
  init_sprites(&game);
  mlx_loop(game.mlx);
}