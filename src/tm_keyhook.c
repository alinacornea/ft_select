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

void select_space(t_select *tm)
{
  t_lsarg *tmp;

  tmp = tm->ls;
  while(tmp->line != 1)
    tmp = tmp->next;
  if (tmp->select == 0)
    tmp->select = 1;
  else
    tmp->select = 0;
  tmp->line = 0;
  tmp->next->line = 1;
}

void move_selected(t_select *tm)
{
  // deselect(tm);
  select_space(tm);
}

void start_begin(t_select *tm)
{
  t_lsarg *tmp;

  tmp = tm->ls;
  while (tmp->line != 1)
    tmp = tmp->next;
  tmp->line = 0;
  tm->ls->line = 1;
}

void start_end(t_select *tm)
{
  t_lsarg *tmp;

  tmp = tm->ls;
  while (tmp->line != 1)
    tmp = tmp->next;
  tmp->line = 0;
  tm->ls->prev->line = 1;
}

// void select_all(t_select *tm)
// {
//
// }

int delete_key(t_select *tm)
{
  t_lsarg *tmp;

  if (tm->ls == tm->ls->next)
  {
    free(tm->ls);
    return(0);
  }
  tmp = tm->ls;
  if (tm->ls->line == 1)
    tm->ls = tmp->next;
  else
  {
    while (tmp->line != 1)
      tmp = tmp->next;
  }
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  tmp->next->line = 1;
  free(tmp->arg);
  free(tmp);
  // count_col(tm);
  tm->count[LINE] -= 1;
  return (1);
}

void return_key(t_select *tm)
{
  t_lsarg *tmp;
  int count;
  int i;

  count = 0;
  tm->enter = 1;
  if (tm->ls->select == 1)
    count++;
  tmp = tm->ls->next;
  while (tmp != tm->ls)
  {
    if(tmp->select == 1)
      count++;
      tmp = tmp->next;
  }
  tm->ret_tab = ft_memalloc(count + 1);
  i = 0;
  if (tm->ls->select == 1)
  {
    tm->ret_tab[i] = ft_strdup(tm->ls->arg);
    i++;
  }
  tm->ret_tab[i] = 0;

}

void print_select(t_select *tm)
{
  int i = 0;
  while (tm->ret_tab[i])
  {
    ft_putstr(tm->ret_tab[i]);
    i++;
  }
}

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
    // (BUFFER == KEY_CTRL_A) ? select_all(tm) : (0);
    (BUFFER == KEY_TAB) ? move_selected(tm) : (0);
    (BUFFER == KEY_HOME) ? start_begin(tm) : (0);
    (BUFFER == KEY_END) ? start_end(tm) : (0);
    (BUFFER == KEY_DELETE || BUFFER == KEY_BACK) ? delete_key(tm) : (0);
    (BUFFER == KEY_RETURN) ? return_key(tm) :  (0);
    tm_clear();
    print_select(tm);
  }
  return (1);
}
