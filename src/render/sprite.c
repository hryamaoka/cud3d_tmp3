#include "render.h"

void init_sprites(t_game *game) {
  int y;
  int x;
  int i;

  game->num_sprites = 0;
  y = 0;
  while (y < game->map.height) {
    x = 0;
    while (x < game->map.width) {
      if (game->map.grid[y][x] == '2')
        game->num_sprites++;
      x++;
    }
    y++;
  }
  if (game->num_sprites > 0) {
    game->sprites = malloc(sizeof(t_sprite) * game->num_sprites);
    if (!game->sprites)
      perror_and_exit("Malloc failed", game);
    y = 0;
    i = 0;
    while (y < game->map.height) {
      x = 0;
      while (x < game->map.width) {
        if (game->map.grid[y][x] == '2') {
          game->sprites[i].x = x + 0.5;
          game->sprites[i].y = y + 0.5;
          game->map.grid[y][x] = '0';
          i++;
        }
        x++;
      }
      y++;
    }
  } else
    game->sprites = NULL;
}

static void render_sprite(t_game *game, int i, int *order) {
  t_sprite_vars vars;
  int stripe;

  setup_sprite_vars(game, i, order, &vars);
  stripe = vars.draw_start_x;
  while (stripe < vars.draw_end_x) {
    draw_stripe(game, &vars, stripe);
    stripe++;
  }
}

void draw_sprites(t_game *game) {
  int i;
  int *order;
  double *dist;

  if (game->num_sprites == 0)
    return;
  order = malloc(sizeof(int) * game->num_sprites);
  dist = malloc(sizeof(double) * game->num_sprites);
  if (!order || !dist)
    return;
  i = 0;
  while (i < game->num_sprites) {
    order[i] = i;
    dist[i] = ((game->player.x - game->sprites[i].x) *
                   (game->player.x - game->sprites[i].x) +
               (game->player.y - game->sprites[i].y) *
                   (game->player.y - game->sprites[i].y));
    i++;
  }
  sort_sprites(order, dist, game->num_sprites);
  i = 0;
  while (i < game->num_sprites) {
    render_sprite(game, i, order);
    i++;
  }
  free(order);
  free(dist);
}
