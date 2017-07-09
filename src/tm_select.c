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

t_list *init_list()
{
  t_list *tmp;

  tmp = ft_memalloc(sizeof(t_list));
  tmp->arg = NULL;
  tmp->select = 0;
  tmp->line = 0;
  tmp->len = 0;
  tmp->next = NULL;
  tmp->prev = NULL;
  return (tmp);
}

t_list *fill_list(char *str)
{
  t_list *ls;

  ls = init_list();
  ls->arg = ft_strdup(str);
  ls->len = ft_strlen(ls->str);
  return (ls);
}

void push_list(t_select *tm, t_list *ls)
{
  t_list *tmp;

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
	t_lst *tmp;

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
