/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:24:06 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:24:06 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int check_digits(char *str) {
  int i;

  i = 0;
  while (str[i]) {
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
      i++;
    if (!str[i])
      break;
    if (!ft_isdigit(str[i]))
      return (0);
    i++;
  }
  return (1);
}

static int set_rgb(t_color *color, char **param) {
  if (!param || !param[0] || !param[1] || !param[2])
    return (0);
  if (!check_digits(param[0]) || !check_digits(param[1]) ||
      !check_digits(param[2]))
    return (0);
  color->r = ft_atoi(param[0]);
  color->g = ft_atoi(param[1]);
  color->b = ft_atoi(param[2]);
  if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 ||
      color->b < 0 || color->b > 255)
    return (0);
  return (1);
}

static int validate_commas(char *line) {
  int i;
  int comma_count;

  i = 0;
  comma_count = 0;
  while (line[i]) {
    if (line[i] == ',')
      comma_count++;
    i++;
  }
  if (comma_count != 2)
    return (0);
  return (1);
}

static int parse_rgb_line(char *line, t_color *color) {
  char **param;
  int ret;
  int i;
  size_t len;

  if (color->r != -1)
    return (0);
  len = ft_strlen(line);
  while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r' ||
                     line[len - 1] == ' ' || line[len - 1] == '\t')) {
    line[len - 1] = '\0';
    len--;
  }
  if (!validate_commas(line))
    return (0);
  param = ft_split(line, ',');
  i = 0;
  while (param && param[i])
    i++;
  if (i != 3) {
    free_split(param);
    return (0);
  }
  ret = set_rgb(color, param);
  free_split(param);
  return (ret);
}

int parse_color(char *line, t_game *game) {
  char **split;
  int ret;

  split = ft_split(line, ' ');
  if (!split || !split[0] || !split[1]) {
    free_split(split);
    return (0);
  }
  ret = 0;
  if (!ft_strncmp("F", split[0], 2)) {
    if (!parse_rgb_line(split[1], &game->floor)) {
      free_split(split);
      perror_and_exit("Invalid Floor color", game);
    }
    ret = 1;
  } else if (!ft_strncmp("C", split[0], 2)) {
    if (!parse_rgb_line(split[1], &game->ceiling)) {
      free_split(split);
      perror_and_exit("Invalid Ceiling color", game);
    }
    ret = 1;
  }
  free_split(split);
  return (ret);
}
