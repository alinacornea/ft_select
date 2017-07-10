/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tm_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 01:21:30 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 01:22:56 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_lsarg *init_list()
{
  t_lsarg *tmp;

  tmp = ft_memalloc(sizeof(t_lsarg));
  tmp->arg = NULL;
  tmp->select = 0;
  tmp->line = 0;
  tmp->len = 0;
  tmp->next = NULL;
  tmp->prev = NULL;
  return (tmp);
}

t_lsarg *fill_list(char *str)
{
  t_lsarg *ls;

  ls = init_list();
  ls->arg = ft_strdup(str);
  ls->len = ft_strlen(ls->arg);
  return (ls);
}

void push_list(t_select *tm, t_lsarg *ls)
{
  t_lsarg *tmp;

  if (tm->ls == NULL)
  {
    ls->prev = ls;
    ls->next = ls;
    tm->ls = ls;
    ls->line = 1;
  }
  else{
    tmp = tm->ls->prev;
    tmp->next = ls;
    ls->next = tm->ls;
    ls->prev = tmp;
    tm->ls->prev = ls;
  }
}
void parse_arg(char **argv, t_select *tm)
{
	int i;
	t_lsarg *tmp;

	i = 1;
	while (argv[i])
	{
		tmp = init_list();
		tmp = fill_list(argv[i]);
		push_list(tm, tmp);
		i++;
	}
	tm->count[LINE] = i;
}
