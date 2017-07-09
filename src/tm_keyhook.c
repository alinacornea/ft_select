/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tm_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 01:21:18 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 01:21:20 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int tm_keyhook(t_select *tm)
{
  char buff[5];

  ft_bzero(buff, 5);
  read(0, buff, 4);
  if (BUFFER == KEY_ESC)
    return (0);
  if (check_size(tm))
  {
    (BUFFER == KEY_DOWN) ? move_down(tm) : (0);
    (BUFFER == KEY_UP) ? move_up(tm) : (0);
    (BUFFER == KEY_SPACE) ? select_space(tm) : (0);
    (BUFFER == KEY_CTRL_A) ? select_all(tm) : (0);
    (BUFFER == KEY_TAB) ? move_selected(tm) : (0);
    (BUFFER == KEY_HOME) ? start_beggining(tm) : (0);
    (BUFFER == KEY_DELETE || BUFFER == KEY_BACK) ? delete_key(tm) : (0);
    (BUFFER == KEY_RETURN) ? return_key(tm); (0);
    tm_clear();
    print_select(tm);
  }
  return (1);
}
