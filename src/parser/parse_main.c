/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:24:24 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 16:48:41 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int process_elem_line(char *line, t_game *game, int *count) {
  if (is_empty_line(line)) {
    free(line);
    return (1);
  }
  {
    int i;

    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
      i++;
    if (line[i] == '#' || (line[i] == '/' && line[i + 1] == '/')) {
      free(line);
      return (1);
    }
  }
  if (parse_texture(line, game))
    (*count)++;
  else if (parse_color(line, game))
    (*count)++;
  else
    return (0);
  free(line);
  return (1);
}

char *parse_elem(int fd, t_game *game) {
  char *line;
  int elem_count;

  elem_count = 0;
  while (1) {
    line = get_next_line(fd);
    if (!line)
      break;
    if (!process_elem_line(line, game, &elem_count)) {
      if (elem_count < 6) {
        free(line);
        perror_and_exit("Unknown identifier", game);
      }
      return (line);
    }
  }
  if (elem_count < 6)
    perror_and_exit("Missing elements", game);
  return (NULL);
}

void parse(char *filename, t_game *game) {
  int fd;
  char *first_line;

  fd = open(filename, O_RDONLY);
  if (fd < 0) {
    perror_and_exit("Could not open file", game);
    return;
  }
  first_line = parse_elem(fd, game);
  if (!parse_map(fd, game, first_line))
    perror_and_exit("Invalid map", game);
  if (!check_map_chars(game))
    perror_and_exit("Invalid map characters", game);
  if (!check_map_closed(game))
    perror_and_exit("Map is not closed", game);
  if (!find_player(game))
    perror_and_exit("Invalid player", game);
}