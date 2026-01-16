#include "parse.h"

static int is_valid_char(char c) {
  if (c == '0' || c == '1' || c == '2' || c == 'D')
    return (1);
  if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
    return (1);
  if (c == ' ')
    return (1);
  return (0);
}

int check_map_chars(t_game *game) {
  int y;
  int x;

  y = 0;
  while (y < game->map.height) {
    x = 0;
    while (x < game->map.width) {
      if (!is_valid_char(game->map.grid[y][x]))
        return (0);
      x++;
    }
    y++;
  }
  return (1);
}

static int is_walkable(char c) {
  if (c == '1' || c == ' ')
    return (0);
  return (1);
}

static int check_surroundings(t_game *game, int x, int y) {
  if (game->map.grid[y][x] == '0' || game->map.grid[y][x] == '2' ||
      game->map.grid[y][x] == 'D' || ft_strchr("NSWE", game->map.grid[y][x])) {
    if (x == 0 || x == game->map.width - 1 || y == 0 ||
        y == game->map.height - 1)
      return (0);
    if (game->map.grid[y - 1][x] == ' ' || game->map.grid[y + 1][x] == ' ' ||
        game->map.grid[y][x - 1] == ' ' || game->map.grid[y][x + 1] == ' ')
      return (0);
  }
  return (1);
}

int check_map_closed(t_game *game) {
  int y;
  int x;
  char **grid;

  grid = game->map.grid;
  y = 0;
  while (y < game->map.height) {
    x = 0;
    while (x < game->map.width) {
      if (is_walkable(grid[y][x])) {
        if (!check_surroundings(game, x, y))
          return (0);
      }
      x++;
    }
    y++;
  }
  return (1);
}
