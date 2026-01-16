#include "parse.h"

/* Map parsing helpers are in parse_map_utils.c */

static int process_map_line(char *line, char ***temp_map, int *height,
                            int *max_width, int *map_ended) {
  int current_width;

  if (is_empty_line(line)) {
    if (*height > 0)
      *map_ended = 1;
    free(line);
    return (1);
  }
  if (*map_ended) {
    free(line);
    return (0);
  }
  cleanup_line(line);
  current_width = ft_strlen(line);
  if (*max_width < current_width)
    *max_width = current_width;
  *temp_map = change_line_to_map(*temp_map, line, *height);
  if (!*temp_map) {
    free(line);
    return (0);
  }
  (*height)++;
  return (1);
}

static int normalize_map(t_game *game, char **temp_map, int height,
                         int max_width) {
  int i;
  char *new_row;

  i = 0;
  while (i < height) {
    new_row = malloc(max_width + 1);
    if (!new_row)
      return (0);
    ft_memset(new_row, ' ', max_width);
    new_row[max_width] = '\0';
    ft_memcpy(new_row, temp_map[i], ft_strlen(temp_map[i]));
    free(temp_map[i]);
    temp_map[i] = new_row;
    i++;
  }
  game->map.grid = temp_map;
  game->map.height = height;
  game->map.width = max_width;
  return (1);
}

static int read_lines(int fd, char ***temp_map, int *height, int *max_width,
                      char *first_line) {
  char *line;
  int map_ended;

  map_ended = 0;
  line = first_line;
  while (line) {
    if (!process_map_line(line, temp_map, height, max_width, &map_ended)) {
      if (*temp_map)
        free_split(*temp_map);
      return (0);
    }
    line = get_next_line(fd);
  }
  return (1);
}

int parse_map(int fd, t_game *game, char *first_line) {
  char **temp_map;
  int height;
  int max_width;

  height = 0;
  max_width = 0;
  temp_map = NULL;
  if (!read_lines(fd, &temp_map, &height, &max_width, first_line))
    return (0);

  if (height == 0) {
    if (temp_map)
      free_split(temp_map);
    return (0);
  }
  if (!normalize_map(game, temp_map, height, max_width)) {
    if (temp_map)
      free_split(temp_map);
    return (0);
  }
  return (1);
}
