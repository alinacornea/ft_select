/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tm_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 01:21:38 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 01:21:39 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select *tm_stok(t_select *tm, int i)
{
  static t_select *tmp = NULL;

  if (i == 0)
    tmp = tm;
  return (tmp);
}

int check_size(t_select *tm)
{
  if (tm->row < 2 || tm->col < 6)
  {
    tm_clear();
    printf("Windows terminal to small\n");
    return (0);
  }
  else{
    tm_clear();
    print_list(tm);
  }
  return (1);
}

void re_size(void)
{
  t_select *tm;
  struct winsize win;

  tm = NULL;
  // tm = tm_stock(tm, 1);
  tm_clear();
  ioctl(0, TIOCGWINSZ, &win);
  tm->col = win.ws_col;
  tm->row = win.ws_row;
  check_size(tm);
}
