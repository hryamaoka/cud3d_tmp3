#include "cub3d.h"

#include "input.h"
#include "keys.h"

void interact_door(t_game *game) {
  int target_x;
  int target_y;

  target_x = (int)(game->player.x + game->player.dir_x);
  target_y = (int)(game->player.y + game->player.dir_y);
  if (target_x >= 0 && target_x < game->map.width && target_y >= 0 &&
      target_y < game->map.height) {
    if (game->map.grid[target_y][target_x] == 'D')
      game->map.grid[target_y][target_x] = 'O';
    else if (game->map.grid[target_y][target_x] == 'O') {
      if ((int)game->player.x == target_x && (int)game->player.y == target_y)
        return;
      game->map.grid[target_y][target_x] = 'D';
    }
  }
}

int key_press(int keycode, t_game *game) {
  if (keycode == KEY_ESC)
    close_game(game);
  else if (keycode == KEY_W)
    move_forward(game);
  else if (keycode == KEY_S)
    move_backward(game);
  else if (keycode == KEY_A)
    move_left(game);
  else if (keycode == KEY_D)
    move_right(game);
  else if (keycode == KEY_E)
    interact_door(game);
  else if (keycode == KEY_LEFT)
    rotate_left(game);
  else if (keycode == KEY_RIGHT)
    rotate_right(game);
  return (0);
}
