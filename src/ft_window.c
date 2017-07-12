/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:49:32 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int check_size_window(t_select *arg)
{
  if (arg->height - 2 < arg->count_lines)
  {
    tputs(tgetstr("cl", NULL), 1, pputchar);
    return (0);
  }
  // else if(arg->begin->name_len > arg->width)
  // {
  //   tputs(tgetstr("cl", NULL), 1, pputchar);
  //   return (0);
  // }
  else
  {
    tputs(tgetstr("cl", NULL), 1, pputchar);
    tm_printlist(arg);
  }
  return (1);
}

void resize_window(void)
{
  t_select *arg;
  struct winsize win;

  arg = NULL;
  tputs(tgetstr("cl", NULL), 1, pputchar);
  ioctl(0, TIOCGWINSZ, &win);
  arg->height= win.ws_row;
  arg->width = win.ws_col;
}
