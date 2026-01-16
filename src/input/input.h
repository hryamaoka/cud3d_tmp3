/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:23:52 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:23:52 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
#define INPUT_H

#include "cub3d.h"

#define ROT_SPEED 0.05
#define MOVE_SPEED 0.1
#define COLLISION_BUFFER 0.2

void move_forward(t_game *game);
void move_backward(t_game *game);
void move_left(t_game *game);
void move_right(t_game *game);
void rotate_left(t_game *game);
void rotate_right(t_game *game);
void interact_door(t_game *game);

#endif
