/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 01:21:27 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 01:21:28 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void print_list(t_select *tm)
{
  t_lsarg *tmp;

  tmp = NULL;
  select_view(tm->ls);
  ft_putstr(tm->ls->arg);
}
