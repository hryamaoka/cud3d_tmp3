#include "cub3d.h"

int check_filename(char *filename) {
  char *extention;
  int diff;

  if (!filename)
    return (0);
  extention = ft_strrchr(filename, '.');
  if (!extention)
    return (0);
  diff = ft_strncmp(extention, ".cub", 5);
  if (diff)
    return (0);
  return (1);
}