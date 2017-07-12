/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcornea <alcornea@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:38:23 by alcornea          #+#    #+#             */
/*   Updated: 2017/07/08 13:49:32 by alcornea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "colors.h"
/*
us - turn on underline mode
so - standout mode
se - leave standout mode
ue - off underline mode
*/

void select_view(t_lsarg *list)
{
  if (list->line == 1 && list->select == 1)
  {
    tputs(tgetstr("us", NULL), 1, pputchar);
    tputs(tgetstr("so", NULL), 1, pputchar);
    ft_putstr_fd(C_YELLOW, 2);
    ft_putendl_fd(list->name, 2);
    ft_putstr_fd(C_RES, 2);
    tputs(tgetstr("se", NULL), 1, pputchar);
    tputs(tgetstr("ue", NULL), 1, pputchar);
  }
  else if (list->line == 1)
  {
  	tputs(tgetstr("us", NULL), 1, pputchar);
  	ft_putstr_fd(C_YELLOW, 2);
  	ft_putendl_fd(list->name, 2);
  	ft_putstr_fd(C_RES, 2);
  	tputs(tgetstr("ue", NULL), 1, pputchar);
  }
  else if (list->select == 1)
  {
    tputs(tgetstr("so", NULL), 1, pputchar);
  	ft_putstr_fd(C_YELLOW, 2);
  	ft_putendl_fd(list->name, 2);
  	ft_putstr_fd(C_RES, 2);
  	tputs(tgetstr("se", NULL), 1, pputchar);
  }
  else
    ft_putendl_fd(list->name, 2);
}

void	print_return(t_select *arg)
{
	int		i;

	i = 0;
	while (arg->ret_tab[i])
	{
		ft_putstr(arg->ret_tab[i]);
		if (arg->ret_tab[i + 1])
			ft_putchar(' ');
		i++;
	}
}

void tm_printlist(t_select *arg)
{
  t_lsarg *tmp;

  tmp = NULL;
  select_view(arg->begin);
  tmp = arg->begin->next;
  while (tmp != arg->begin)
  {
    select_view(tmp);
    tmp = tmp->next;
  }
}
