/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tm_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 01:21:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 01:21:24 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void move_up(t_select *tm)
{
  t_lsarg *tmp;

  tmp = tm->ls;
  while (tmp->line != 1)
    tmp = tmp->next;
  tmp->line = 0;
  tmp->prev->line = 1;
}

void move_down(t_select *tm)
{
  t_lsarg *tmp;

  tmp = tm->ls;
  while (tmp->line != 1)
    tmp = tmp->next;
  tmp->line = 0;
  tmp->next->line = 1;
}
