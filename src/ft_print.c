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

static void select_format(t_lsarg *list)
{
  if (list->cursor == 1 && list->select == 1)
    ft_printf(C_RED"%s\n"C_RES, list->name);
  else if (list->cursor == 1)
  {
  	tputs(tgetstr("us", NULL), 1, pputchar);
    ft_printf(C_YELLOW"%s\n"C_RES, list->name);
  	tputs(tgetstr("ue", NULL), 1, pputchar);
  }
  else if (list->select == 1)
  {
    tputs(tgetstr("so", NULL), 1, pputchar);
    ft_printf(C_YELLOW"%s\n"C_RES, list->name);
    tputs(tgetstr("se", NULL), 1, pputchar);
  }
  else
    ft_printf("%s\n", list->name);
}

void	print_return(t_select *arg)
{
	int		i;
  int   count;

	i = 0;
  count = 0;
  while (arg->ret_tab[count])
    count++;
	while (arg->ret_tab[i])
	{
    (i < count - 1) ? ft_printf(BOLD"%s ", arg->ret_tab[i]) :
    (ft_printf("%s\n", arg->ret_tab[i]));
    ft_strdel(&arg->ret_tab[i]);
		i++;
	}
  arg->ret_tab[i] = NULL;
}

void tm_printlist(t_select *arg)
{
  t_lsarg *tmp;

  tmp = NULL;
  select_format(arg->begin);
  tmp = arg->begin->next;
  while (tmp != arg->begin)
  {
    select_format(tmp);
    tmp = tmp->next;
  }
}
