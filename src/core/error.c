/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:34:15 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/13 16:32:01 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void perror_and_exit(char *msg, t_game *game) {
  ft_putendl_fd("Error", STDERR_FILENO);
  ft_putendl_fd(msg, STDERR_FILENO);
  if (game != NULL)
    free_all(game);
  exit(1);
}