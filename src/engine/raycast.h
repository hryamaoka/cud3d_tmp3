/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:23:44 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:23:44 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_INTERNAL_H
#define RAYCAST_INTERNAL_H

#include "cub3d.h"

void perform_dda(t_game *game);
void select_texture(t_game *game, t_img **tex);
void init_ray_step_x(t_game *game);
void init_ray_step_y(t_game *game);

#endif
