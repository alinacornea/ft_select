/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:49:32 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void free_list(t_select *arg)
{
	arg->begin->name ? free(arg->begin->name) : (0);
	arg->ret_tab ? ft_strdel(arg->ret_tab) : (0);

}

t_lsarg *tm_init_list(void)
{
  t_lsarg *tmp;

  tmp = (t_lsarg *)malloc(sizeof(t_lsarg));
  tmp->name = NULL;
  tmp->select = 0;
  tmp->cursor = 0;
  tmp->name_len = 0;
  tmp->next = NULL;
  tmp->prev = NULL;
  return (tmp);
}

/*

*/

void create_list(t_select *arg, t_lsarg *ls)
{
  t_lsarg *tmp;

  if (arg->begin == NULL)
  {
    ls->prev = ls;
    ls->next = ls;
    arg->begin = ls;
    ls->cursor = 1;
  }
  else
	{
    tmp = arg->begin->prev;
    tmp->next = ls;
    ls->next = arg->begin;
    ls->prev = tmp;
    arg->begin->prev = ls;
  }
}

/*
** tm_makelist() will create the list based on the arguments introduced
** using the t_select and t_lasarg structs;
** rows-counting the number of lines made;
** name-len will be using in order to find out the window size;
*/

void tm_makelist(char **argv, t_select *arg)
{
  int 		rows;
  t_lsarg	*tmp;

  rows = 1;
  while (argv[rows])
  {
    tmp = tm_init_list();
    tmp->name = ft_strdup(argv[rows]);
    tmp->name_len = ft_strlen(tmp->name);
    create_list(arg, tmp);
    rows++;
  }
  arg->count_lines = rows;
}
