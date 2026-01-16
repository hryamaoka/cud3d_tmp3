/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyamaoka <hyamaoka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:24:52 by hyamaoka          #+#    #+#             */
/*   Updated: 2026/01/16 14:24:53 by hyamaoka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int is_empty_line(char *line) {
  int i;

  i = 0;
  while (line[i]) {
    if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r')
      return (0);
    i++;
  }
  return (1);
}
