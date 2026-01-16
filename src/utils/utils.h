#ifndef UTILS_H
#define UTILS_H

#include "cub3d.h"

int ft_abs(int n);
void perror_and_exit(char *msg, t_game *game);
void free_all(t_game *game);
void free_split(char **split);

#endif
