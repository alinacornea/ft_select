/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:49:32 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void get_selected(t_select *arg, int count)
{
    t_lsarg *tmp;
    int i;

    i = 0;
    tmp = NULL;
    arg->ret_tab = (char **)malloc(sizeof(char*) * (count + 1));
    if (arg->begin->select == 1)
    {
      arg->ret_tab[i] = ft_strdup(arg->begin->name);
      i++;
    }
    tmp = arg->begin->next;
    while (tmp != arg->begin)
    {
      if (tmp->select == 1)
      {
        arg->ret_tab[i] = ft_strdup(tmp->name);
        i++;
      }
      tmp = tmp->next;
    }
    arg->ret_tab[i] = 0;
}

void return_key(t_select *arg)
{
    t_lsarg *tmp;
    int count;

    count = 0;
    arg->enter = 1;
    if (arg->begin->select == 1)
      count++;
    tmp = arg->begin->next;
    while (tmp != arg->begin)
    {
      if (tmp->select == 1)
        count++;
      tmp = tmp->next;
    }
    get_selected(arg, count);
}

void position_cursor(t_select *arg, char *buff)
{
  t_lsarg *tmp;

  tmp = arg->begin;
  while(tmp->line != 1)
    tmp = tmp->next;
  tmp->line = 0;
  (INPUT == KEY_HOME) ? (arg->begin->line = 1) : (arg->begin->prev->line = 1);
}

void select_space(t_select *arg)
{
  t_lsarg *tmp;

  tmp = arg->begin;
  while (tmp->line != 1)
    tmp = tmp->next;
  (tmp->select == 0) ? (tmp->select = 1) : (tmp->select = 0);
  tmp->line = 0;
  tmp->next->line = 1;
}

void arrow_up_down(t_select *arg, char *buff)
{
  t_lsarg *tmp;

  tmp = arg->begin;
  while (tmp->line != 1)
    tmp = tmp->next;
  tmp->line = 0;
  (INPUT == KEY_UP) ? (tmp->prev->line = 1) : (tmp->next->line = 1);
}

/*
** delete_key()
** next argument will be setup as previous and previos as first in order to delete_key
** line by line and than exit if there are no more arguments;
** count_line will decrease;
*/

int delete_key(t_select *arg)
{
  t_lsarg *tmp;

  if (arg->begin == arg->begin->next)
  {
    free(arg->begin);
    return (0);
  }
  tmp = arg->begin;
  if (arg->begin->line == 1)
    arg->begin = tmp->next;
  else
  {
    while (tmp->line != 1)
      tmp = tmp->next;
  }
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  tmp->next->line = 1;
  free(tmp->name);
  free(tmp);
  arg->count_lines--;
  return (1);
}

/*
  setup the keyhooks...complete the whole comment
*/

int tm_keyhook(t_select *arg)
{
  char buff[5];

  ft_bzero(buff, 5);
  read(0, buff, 4);
  if (INPUT == KEY_ESC)
    return (0);
  (INPUT == KEY_UP || INPUT == KEY_DOWN) ? arrow_up_down(arg, buff) : (0);
  (INPUT == KEY_SPACE) ? select_space(arg) : (0);
  (INPUT == KEY_HOME || INPUT == KEY_END) ? position_cursor(arg, buff) : (0);
  if (INPUT == KEY_DELETE || INPUT == KEY_BACK)
  {
    if (!delete_key(arg))
      return (0);
  }
  if (INPUT == KEY_RETURN)
  {
    return_key(arg);
    return (0);
  }
  tputs(tgetstr("cl", NULL), 1, pputchar);
  tm_printlist(arg);
  return (1);
}
