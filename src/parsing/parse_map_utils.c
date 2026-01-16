/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/16 11:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char **change_line_to_map(char **map, char *line, int height) {
  char **new_map;
  int i;

  new_map = malloc(sizeof(char *) * (height + 2));
  if (!new_map)
    return (NULL);
  i = 0;
  while (i < height) {
    new_map[i] = map[i];
    i++;
  }
  new_map[height] = line;
  new_map[height + 1] = NULL;
  if (map)
    free(map);
  return (new_map);
}

void cleanup_line(char *line) {
  char *newline;

  newline = ft_strchr(line, '\n');
  if (newline)
    *newline = '\0';
  newline = ft_strchr(line, '\r');
  if (newline)
    *newline = '\0';
}
