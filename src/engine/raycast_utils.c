#include "raycast.h"

void perform_dda(t_game *game) {
  while (game->ray.hit == 0) {
    if (game->ray.side_dist_x < game->ray.side_dist_y) {
      game->ray.side_dist_x += game->ray.delta_dist_x;
      game->ray.map_x += game->ray.step_x;
      game->ray.side = 0;
    } else {
      game->ray.side_dist_y += game->ray.delta_dist_y;
      game->ray.map_y += game->ray.step_y;
      game->ray.side = 1;
    }
    if (game->ray.map_x < 0 || game->ray.map_x >= game->map.width ||
        game->ray.map_y < 0 || game->ray.map_y >= game->map.height) {
      game->ray.hit = 1;
      break;
    }
    if (game->map.grid[game->ray.map_y][game->ray.map_x] == '1' ||
        game->map.grid[game->ray.map_y][game->ray.map_x] == 'D')
      game->ray.hit = 1;
  }
}

void select_texture(t_game *game, t_img **tex) {
  if (game->map.grid[game->ray.map_y][game->ray.map_x] == 'D') {
    *tex = &game->door_tex;
  } else if (game->ray.side == 0) {
    if (game->ray.ray_dir_x > 0)
      *tex = &game->wall_tex[3];
    else
      *tex = &game->wall_tex[2];
  } else {
    if (game->ray.ray_dir_y > 0)
      *tex = &game->wall_tex[1];
    else
      *tex = &game->wall_tex[0];
  }
}

void init_ray_step_x(t_game *game) {
  if (game->ray.ray_dir_x < 0) {
    game->ray.step_x = -1;
    game->ray.side_dist_x =
        (game->player.x - game->ray.map_x) * game->ray.delta_dist_x;
  } else {
    game->ray.step_x = 1;
    game->ray.side_dist_x =
        (game->ray.map_x + 1.0 - game->player.x) * game->ray.delta_dist_x;
  }
}

void init_ray_step_y(t_game *game) {
  if (game->ray.ray_dir_y < 0) {
    game->ray.step_y = -1;
    game->ray.side_dist_y =
        (game->player.y - game->ray.map_y) * game->ray.delta_dist_y;
  } else {
    game->ray.step_y = 1;
    game->ray.side_dist_y =
        (game->ray.map_y + 1.0 - game->player.y) * game->ray.delta_dist_y;
  }
}
