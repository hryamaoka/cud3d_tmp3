#ifndef PARSE_H
#define PARSE_H

#include "cub3d.h"

int parse_map(int fd, t_game *game, char *first_line);

int is_empty_line(char *line);

int parse_texture(char *line, t_game *game);
int parse_color(char *line, t_game *game);

int find_player(t_game *game);

int check_map_chars(t_game *game);
int check_map_closed(t_game *game);

char **change_line_to_map(char **map, char *line, int height);
void cleanup_line(char *line);

#endif