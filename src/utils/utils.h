/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:51:40 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:51:40 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include "cub3d.h"

int ft_abs(int n);
void perror_and_exit(char *msg, t_game *game);
void free_all(t_game *game);
void free_split(char **split);

#endif
