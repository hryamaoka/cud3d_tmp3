/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:24:49 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:24:49 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "parse.h"

static int set_texture(char **texture, char *path) {
  size_t len;

  if (*texture)
    return (0);
  len = ft_strlen(path);
  while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == '\r' ||
                     path[len - 1] == ' ' || path[len - 1] == '\t')) {
    path[len - 1] = '\0';
    len--;
  }
  if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4))
    return (0);
  *texture = ft_strdup(path);
  return (1);
}

int parse_texture(char *line, t_game *game) {
  char **split;
  int ret;

  split = ft_split(line, ' ');
  if (!split || !split[0] || !split[1]) {
    free_split(split);
    return (0);
  }
  ret = 0;
  if (!ft_strncmp("NO", split[0], 3)) {
    if (!set_texture(&game->tex.no, split[1])) {
      free_split(split);
      perror_and_exit("Invalid NO texture", game);
    }
    ret = 1;
  } else if (!ft_strncmp("SO", split[0], 3)) {
    if (!set_texture(&game->tex.so, split[1])) {
      free_split(split);
      perror_and_exit("Invalid SO texture", game);
    }
    ret = 1;
  } else if (!ft_strncmp("WE", split[0], 3)) {
    if (!set_texture(&game->tex.we, split[1])) {
      free_split(split);
      perror_and_exit("Invalid WE texture", game);
    }
    ret = 1;
  } else if (!ft_strncmp("EA", split[0], 3)) {
    if (!set_texture(&game->tex.ea, split[1])) {
      free_split(split);
      perror_and_exit("Invalid EA texture", game);
    }
    ret = 1;
  }
  free_split(split);
  return (ret);
}
